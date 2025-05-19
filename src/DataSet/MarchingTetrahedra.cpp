///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/MarchingTetrahedra.h>

#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/DataSet/RegularScalarGrid.h>

using std::isfinite;
using std::vector;
using Vectoid::Core::Axis;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace DataSet {

MarchingTetrahedra::MarchingTetrahedra() 
        : grid_{nullptr},
          isoValue_{0.0f},
          xCursor_{0},
          yCursor_{0},
          zCursor_{0} {
    edgeVertices_[0] = TwoIds{0, 1};
    edgeVertices_[1] = TwoIds{1, 2};
    edgeVertices_[2] = TwoIds{2, 0};
    edgeVertices_[3] = TwoIds{0, 3};
    edgeVertices_[4] = TwoIds{1, 3};
    edgeVertices_[5] = TwoIds{2, 3};

    AddCase(0u, { });
    AddCase(1u, { 2, 0, 3 });
    AddCase(2u, { 0, 1, 4 });
    AddCase(4u, { 1, 2, 5 });
    AddCase(8u, { 3, 4, 5 });
    AddCase(3u, { 2, 1, 4, 2, 4, 3 });
    AddCase(5u, { 0, 3, 5, 0, 5, 1 });
    AddCase(9u, { 0, 4, 5, 0, 5, 2 });

    vector<int> tetrahedra { 0, 1, 4, 13,
                             1, 2, 4, 13,
                             2, 5, 4, 13,
                             5, 8, 4, 13,
                             8, 7, 4, 13,
                             7, 6, 4, 13,
                             6, 3, 4, 13,
                             3, 0, 4, 13  };
    AddTetrahedra(tetrahedra);
    RotateTetrahedra(Axis::X, tetrahedra);
    AddTetrahedra(tetrahedra);
    RotateTetrahedra(Axis::X, tetrahedra);
    AddTetrahedra(tetrahedra);
    RotateTetrahedra(Axis::X, tetrahedra);
    AddTetrahedra(tetrahedra);
    RotateTetrahedra(Axis::Y, tetrahedra);
    AddTetrahedra(tetrahedra);
    RotateTetrahedra(Axis::Y, tetrahedra);
    RotateTetrahedra(Axis::Y, tetrahedra);
    AddTetrahedra(tetrahedra);
}

void MarchingTetrahedra::ExtractIsoSurface(const RegularScalarGrid &grid, float isoValue) {
    if (isfinite(isoValue)) {
        grid_     = &grid;
        isoValue_ = isoValue;
        
        int numPointsX; 
        int numPointsY; 
        int numPointsZ;
        grid_->GetDimensions(numPointsX, numPointsY, numPointsZ);
        if ((numPointsX % 2 == 1) && (numPointsY % 2 == 1) && (numPointsZ % 2 == 1)) {
            for (zCursor_ = 0; zCursor_ < numPointsZ - 2; ++zCursor_) {
                for (yCursor_ = 0; yCursor_ < numPointsY - 2; ++yCursor_) {
                    for (xCursor_ = 0; xCursor_ < numPointsX - 2; ++xCursor_) {
                        SetUpMetaCube();
                        GenerateTrianglesForMetaCube();
                    }
                }
            }
        }
    }

    grid_ = nullptr;
}

// ---

void MarchingTetrahedra::SetUpMetaCube() {
    int i { 0 };
    for (int y = 0; y < 3; ++y) {
        int yPoint { yCursor_ + y };
        for (int z = 0; z < 3; ++z) {
            int zPoint { zCursor_ + 2 - z };
            for (int x = 0; x < 3; ++x) {
                int xPoint { xCursor_ + x };
                vertices_[i]     = grid_->Point(xPoint, yPoint, zPoint);
                vertexValues_[i] = grid_->Value(xPoint, yPoint, zPoint);
                ++i;
            }
        }
    }
}

void MarchingTetrahedra::GenerateTrianglesForMetaCube() {
    int i { 0 };
    while (i + 3 < static_cast<int>(tetrahedronSubDivision_.size())) {
        GenerateTrianglesForTetrahedron(tetrahedronSubDivision_[i],     tetrahedronSubDivision_[i + 1],
                                        tetrahedronSubDivision_[i + 2], tetrahedronSubDivision_[i + 3]);
        i += 4;
    }

}

void MarchingTetrahedra::GenerateTrianglesForTetrahedron(int vertexIndex0, int vertexIndex1, int vertexIndex2,
                                                         int vertexIndex3) {
    vertexMap_[0] = vertexIndex0;
    vertexMap_[1] = vertexIndex1;
    vertexMap_[2] = vertexIndex2;
    vertexMap_[3] = vertexIndex3;

    // Select tetrahedron case...
    unsigned int tetrahedronCase { 0u };
    for (int i = 0; i < 4; ++i) {
        if (vertexValues_[vertexMap_[i]] >= isoValue_)
            tetrahedronCase |= bitValues[i];
    }
    vector<int> &edges = cases_[tetrahedronCase].edges;

    // Compute intersection points for the relevant edges...
    // Note: This can be optimized, as edges may get computed multiple times!
    for (int edge : edges) {
        int           &vertex0 { vertexMap_[edgeVertices_[edge].id0] };
        int           &vertex1 { vertexMap_[edgeVertices_[edge].id1] };
        Vector<float> &point0  { vertices_[vertex0] };
        Vector<float> &point1  { vertices_[vertex1] };
        float         &value0  { vertexValues_[vertex0] };
        float         &value1  { vertexValues_[vertex1] };
        // The interpolated intersection points on the respective edges of neighboring tetrahedra must be identical on
        // bit level, so we must take great care that they are computed exactly the same way (think floating point
        // arithmetics)...
        if (value0 < value1) {
            edgeIntersections_[edge] = CombineAffine((isoValue_ - value0) / (value1 - value0), point0, point1);
        } else if (value0 > value1) {
            edgeIntersections_[edge] = CombineAffine((isoValue_ - value1) / (value0 - value1), point1, point0);
        } else {
            edgeIntersections_[edge] = .5f*point0 + .5f*point1;
        }
    }
    
    // Generate triangles...
    int firstEdge { 0 };
    while (firstEdge + 2 < static_cast<int>(edges.size())) {
        ThreePoints{edgeIntersections_[edges[firstEdge]],
                    edgeIntersections_[edges[firstEdge + 1]],
                    edgeIntersections_[edges[firstEdge + 2]]};
        firstEdge += 3;
    }
}

void MarchingTetrahedra::AddCase(unsigned int caseId, const vector<int> &edges) { 
    cases_[caseId].edges.clear();
    for (int edge : edges) {
        cases_[caseId].edges.push_back(edge);
    }

    unsigned int inverseCaseId { 0u }; 
    for (unsigned int i = 0u; i < 4u; ++i) {
        if ((caseId & bitValues[i]) == 0u)
            inverseCaseId |= bitValues[i];
    }

    cases_[inverseCaseId].edges.clear();
    for (unsigned int i = 0u; i < edges.size(); ++i) {
        cases_[inverseCaseId].edges.push_back(edges[edges.size() - i - 1u]);
        
    }
}

void MarchingTetrahedra::AddTetrahedra(const vector<int> &tetrahedra) {
    for (int vertex : tetrahedra) {
        tetrahedronSubDivision_.push_back(vertex);
    }
}

void MarchingTetrahedra::RotateTetrahedra(Axis axis, vector<int> &tetrahedra) {
    vector<int> vertexMap;
    if (axis == Axis::X) {    // Rotate around x-axis.
        vertexMap = vector<int>{ 18, 19, 20,  9, 10, 11,  0,  1,  2,
                                 21, 22, 23, 12, 13, 14,  3,  4,  5,
                                 24, 25, 26, 15, 16, 17,  6,  7,  8  };
    } else {    // Rotate around y-axis.
        vertexMap = vector<int>{  6,  3,  0,  7,  4,  1,  8,  5,  2,
                                 15, 12,  9, 16, 13, 10, 17, 14, 11,
                                 24, 21, 18, 25, 22, 19, 26, 23, 20  };
    }

    for (int &vertex : tetrahedra) {
        vertex = vertexMap[vertex];
    }
}

}    // Namespace Vectoid.
}    // Namespace K.
