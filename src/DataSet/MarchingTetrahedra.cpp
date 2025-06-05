///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/MarchingTetrahedra.h>

#include <K/Core/Log.h>
#include <K/Core/NumberTools.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/TriangleHandlerInterface.h>
#include <Vectoid/DataSet/LineSegments.h>
#include <Vectoid/DataSet/RegularScalarGrid.h>
#include <Vectoid/DataSet/ThreeIds.h>

using std::isfinite;
using std::shared_ptr;
using std::to_string;
using std::unordered_map;
using std::vector;
using K::Core::Log;
using K::Core::NumberTools;
using Vectoid::Core::Axis;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::TriangleHandlerInterface;
using Vectoid::Core::TwoPoints;
using Vectoid::Core::Vector;
using Vectoid::DataSet::ThreeIds;

namespace Vectoid {
namespace DataSet {

MarchingTetrahedra::MarchingTetrahedra() 
        : grid_{nullptr},
          isoValue_{0.0f},
          triangleHandler_{nullptr},
          xCursor_{0},
          yCursor_{0},
          zCursor_{0},
          cubePattern_{&cubeTetrahedra_[0][0][0]} {
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
    AddMetaCubeTetrahedra(tetrahedra);
    RotateMetaCubeTetrahedra(Axis::X, tetrahedra);
    AddMetaCubeTetrahedra(tetrahedra);
    RotateMetaCubeTetrahedra(Axis::X, tetrahedra);
    AddMetaCubeTetrahedra(tetrahedra);
    RotateMetaCubeTetrahedra(Axis::X, tetrahedra);
    AddMetaCubeTetrahedra(tetrahedra);
    RotateMetaCubeTetrahedra(Axis::Y, tetrahedra);
    AddMetaCubeTetrahedra(tetrahedra);
    RotateMetaCubeTetrahedra(Axis::Y, tetrahedra);
    RotateMetaCubeTetrahedra(Axis::Y, tetrahedra);
    AddMetaCubeTetrahedra(tetrahedra);

    CollectCubeTetrahedra(0, 0, 0, {  3,  4,  6,  7, 12, 13, 15, 16 });
    CollectCubeTetrahedra(0, 1, 0, { 12, 13, 15, 16, 21, 22, 24, 25 });
    CollectCubeTetrahedra(1, 0, 0, {  4,  5,  7,  8, 13, 14, 16, 17 });
    CollectCubeTetrahedra(1, 1, 0, { 13, 14, 16, 17, 22, 23, 25, 26 });
    CollectCubeTetrahedra(0, 0, 1, {  0,  1,  3,  4,  9, 10, 12, 13 });
    CollectCubeTetrahedra(0, 1, 1, {  9, 10, 12, 13, 18, 19, 21, 22 });
    CollectCubeTetrahedra(1, 0, 1, {  1,  2,  4,  5, 10, 11, 13, 14 });
    CollectCubeTetrahedra(1, 1, 1, { 10, 11, 13, 14, 19, 20, 22, 23 });
}

void MarchingTetrahedra::ExtractIsoSurface(RegularScalarGrid &grid, float isoValue,
                                           TriangleHandlerInterface &triangleHandler) {
    if (isfinite(isoValue)) {
        grid_            = &grid;
        isoValue_        = isoValue;
        triangleHandler_ = &triangleHandler;
        
        int numPointsX; 
        int numPointsY; 
        int numPointsZ;
        grid_->GetDimensions(numPointsX, numPointsY, numPointsZ);
        for (zCursor_ = 0; zCursor_ + 1 < numPointsZ; ++zCursor_) {
            for (yCursor_ = 0; yCursor_ + 1 < numPointsY; ++yCursor_) {
                for (xCursor_ = 0; xCursor_ + 1 < numPointsX; ++xCursor_) {
                    SetUpCube();
                    GenerateTrianglesForCube();
                }
            }
        }
    }

    grid_            = nullptr;
    triangleHandler_ = nullptr;
}

void MarchingTetrahedra::ExtractIsoSurface(const ThreeIds &cube, RegularScalarGrid &grid, float isoValue,
                                           TriangleHandlerInterface &triangleHandler) {
    if (isfinite(isoValue)) {
        grid_            = &grid;
        isoValue_        = isoValue;
        triangleHandler_ = &triangleHandler;
        
        int numPointsX; 
        int numPointsY; 
        int numPointsZ;
        grid_->GetDimensions(numPointsX, numPointsY, numPointsZ);

        xCursor_ = cube.id0;
        yCursor_ = cube.id1;
        zCursor_ = cube.id2;
        NumberTools::Clamp(xCursor_, 0, numPointsX - 2);
        NumberTools::Clamp(yCursor_, 0, numPointsY - 2);
        NumberTools::Clamp(zCursor_, 0, numPointsZ - 2);

        SetUpCube();
        GenerateTrianglesForCube();
    }

    grid_            = nullptr;
    triangleHandler_ = nullptr;
}

void MarchingTetrahedra::SetDebugGeometry(const shared_ptr<LineSegments> &debugGeometry) {
    debugGeometry_ = debugGeometry;
}

// ---

void MarchingTetrahedra::SetUpCube() {
    int i { 0 };
    for (int y = 0; y < 2; ++y) {
        int yPoint { yCursor_ + y };
        for (int z = 0; z < 2; ++z) {
            int zPoint { zCursor_ + 1 - z };
            for (int x = 0; x < 2; ++x) {
                int xPoint { xCursor_ + x };
                vertices_[i]     = grid_->Point(xPoint, yPoint, zPoint);
                vertexValues_[i] = grid_->Value(xPoint, yPoint, zPoint);
                ++i;
            }
        }
    }

    int patternSelectX { ((xCursor_ >> 1) << 1 != xCursor_) ? 1 : 0 };
    int patternSelectY { ((yCursor_ >> 1) << 1 != yCursor_) ? 1 : 0 };
    int patternSelectZ { ((zCursor_ >> 1) << 1 != zCursor_) ? 1 : 0 };
    cubePattern_ = &cubeTetrahedra_[patternSelectX][patternSelectY][patternSelectZ];

    if (debugGeometry_) {
        debugGeometry_->Add(TwoPoints{vertices_[0], vertices_[1]});
        debugGeometry_->Add(TwoPoints{vertices_[1], vertices_[5]});
        debugGeometry_->Add(TwoPoints{vertices_[5], vertices_[4]});
        debugGeometry_->Add(TwoPoints{vertices_[4], vertices_[0]});

        debugGeometry_->Add(TwoPoints{vertices_[2], vertices_[3]});
        debugGeometry_->Add(TwoPoints{vertices_[3], vertices_[7]});
        debugGeometry_->Add(TwoPoints{vertices_[7], vertices_[6]});
        debugGeometry_->Add(TwoPoints{vertices_[6], vertices_[2]});

        debugGeometry_->Add(TwoPoints{vertices_[0], vertices_[2]});
        debugGeometry_->Add(TwoPoints{vertices_[1], vertices_[3]});
        debugGeometry_->Add(TwoPoints{vertices_[5], vertices_[7]});
        debugGeometry_->Add(TwoPoints{vertices_[4], vertices_[6]});
    }
}

void MarchingTetrahedra::GenerateTrianglesForCube() {
    int i { 0 };
    while (i + 3 < static_cast<int>(cubePattern_->size())) {
        GenerateTrianglesForTetrahedron((*cubePattern_)[i],     (*cubePattern_)[i + 1],
                                        (*cubePattern_)[i + 2], (*cubePattern_)[i + 3]);
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
        triangleHandler_->OnTriangle(ThreePoints{edgeIntersections_[edges[firstEdge]],
                                                 edgeIntersections_[edges[firstEdge + 1]],
                                                 edgeIntersections_[edges[firstEdge + 2]]});
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
        if ((caseId & bitValues[i]) == 0u) {
            inverseCaseId |= bitValues[i];
        }
    }

    cases_[inverseCaseId].edges.clear();
    for (unsigned int i = 0u; i < edges.size(); ++i) {
        cases_[inverseCaseId].edges.push_back(edges[edges.size() - i - 1u]);
    }
}

void MarchingTetrahedra::AddMetaCubeTetrahedra(const vector<int> &tetrahedra) {
    for (int vertex : tetrahedra) {
        metaCubeTetrahedra_.push_back(vertex);
    }
}

void MarchingTetrahedra::RotateMetaCubeTetrahedra(Axis axis, vector<int> &tetrahedra) {
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

void MarchingTetrahedra::CollectCubeTetrahedra(int x, int y, int z, const vector<int> &tetrahedra) {
    vector<int> &cubeTetrahedra { cubeTetrahedra_[x][y][z] };
    
    unordered_map<int, int> vertexMap;
    for (vector<int>::size_type i = 0u; i < tetrahedra.size(); ++i) {
        vertexMap[tetrahedra[i]] = i;
    }
    
    vector<int>::size_type cursor { 0u };
    int                    num    { 0  };
    while (cursor + 3u < metaCubeTetrahedra_.size()) {
        bool collect { true };
        for (vector<int>::size_type i = 0u; i < 4u; ++i) {
            if (!vertexMap.contains(metaCubeTetrahedra_[cursor + i])) {
                collect = false;
            }
        }

        if (collect) {
            Log::Print(Log::Level::Debug, this, [&]{ return "collecting tetrahedron:"; });
            for (vector<int>::size_type i = 0u; i < 4u; ++i) {
                cubeTetrahedra.push_back(vertexMap[metaCubeTetrahedra_[cursor + i]]);
                Log::Print(Log::Level::Debug, this, [&]{
                    return "" + to_string(metaCubeTetrahedra_[cursor + i]) + " -> "
                        + to_string(vertexMap[metaCubeTetrahedra_[cursor + i]]);
                }); 
            }

             ++num;
        }

        cursor += 4u;
    }

    Log::Print(Log::Level::Debug, this, [&]{ return "cube group (" + to_string(x) + ", " + to_string(y) + ", "
                                                        + to_string(z) + "): num_tetrahedra=" + to_string(num); });
}

}    // Namespace Vectoid.
}    // Namespace K.
