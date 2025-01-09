///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/TriangleTreeXY.h>

#include <K/Core/Log.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/DataSet/Points.h>
#include <Vectoid/Math/Intersection/PointTriangleIntersectionXY.h>

using std::to_string;
using K::Core::Log;
using Vectoid::Core::Vector;
using Vectoid::Core::ThreePoints;
using Vectoid::Math::Intersection::PointTriangleIntersectionXY;

namespace Vectoid {
namespace DataSet {

TriangleTreeXY::TriangleTreeXY(const std::shared_ptr<Points> &vertices)
        : vertices_(vertices),
          cursor_(-1) {
    // Nop.
}

void TriangleTreeXY::PrepareToProvideTriangles() {
    cursor_ = -1;
}

bool TriangleTreeXY::ProvideNextTriangle(ThreePoints &outTriangle) {
    ++cursor_;
    while (cursor_ < static_cast<int>(triangles_.size())) {
        TriangleInfo &info = triangles_[cursor_];
        if (!info.HasChildren()) {
            outTriangle.point0 = (*vertices_)[info.vertices.id0];
            outTriangle.point1 = (*vertices_)[info.vertices.id1];
            outTriangle.point2 = (*vertices_)[info.vertices.id2];
            return true;
        }
        ++cursor_;
    }

    return false;
}

void TriangleTreeXY::ProvideNormal(Vector<float> &outNormal) {
    outNormal = Vector<float>(0.0f, 1.0f, 0.0f);
}

bool TriangleTreeXY::TriangleError() {
    return triangles_.empty();
}

TriangleTreeXY::TriangleInfo &TriangleTreeXY::operator[](int index) {
    assert((index >= 0) && (index < static_cast<int>(triangles_.size())));
    return triangles_[index];
}

int TriangleTreeXY::Count() const {
    return static_cast<int>(triangles_.size());
}

int TriangleTreeXY::LocateTriangle(const Vector<float> &point, int rootTriangleId) {
    TriangleInfo &info = triangles_[rootTriangleId];
    ThreePoints vertices((*vertices_)[info.vertices.id0], (*vertices_)[info.vertices.id1],
                         (*vertices_)[info.vertices.id2]);
    bool intersects;
    if (PointTriangleIntersectionXY::Compute(point, vertices, &intersects) && intersects) {
        if (!info.HasChildren()) {
            return rootTriangleId;
        }
        else {
            for (int i = 0; i < 3; ++i) {
                int child = info.GetChild(i);
                if (child == -1) {
                    break;
                }
                int triangleId = LocateTriangle(point, child);
                if (triangleId != -1) {
                    return triangleId;
                }
            }
        }
    }

    return -1;
}

void TriangleTreeXY::UpdateTriangleAdjacency(int triangleToUpdateId, int oldAdjacentTriangleId,
                                                      int newAdjacentTriangleId) {
    TriangleInfo &info = triangles_[triangleToUpdateId];
    for (int i = 0; i < 3; ++i) {
        if (info.GetAdjacentTriangle(i) == oldAdjacentTriangleId) {
            info.SetAdjacentTriangle(i, newAdjacentTriangleId);
            break;
        }
    }
}

void TriangleTreeXY::GetIdsForSharedEdge(int triangle0Id, int triangle1Id, int *outSharedEdge0Id,
                                         int *outSharedEdge1Id) {
    *outSharedEdge0Id = -1;
    *outSharedEdge1Id = -1;
    TriangleInfo &info0 = triangles_[triangle0Id];
    TriangleInfo &info1 = triangles_[triangle1Id];
    for (int i = 0; i < 3; ++i) {
        if (info0.GetAdjacentTriangle(i) == triangle1Id) {
            *outSharedEdge0Id = i;
        }
        if (info1.GetAdjacentTriangle(i) == triangle0Id) {
            *outSharedEdge1Id = i;
        }
    }
    assert((*outSharedEdge0Id != -1) && (*outSharedEdge1Id != -1));
}

int TriangleTreeXY::AddTriangle(int parentTriangleId) {
    int id = static_cast<int>(triangles_.size());
    triangles_.push_back(TriangleInfo(-1, -1, -1));
    if (parentTriangleId >= 0) {
        triangles_[parentTriangleId].AddChild(id);
    }
    return id;
}

int TriangleTreeXY::Mod3(int value) {
    while (value > 2) {
        value -= 3;
    }
    return value;
}

TriangleTreeXY::TriangleInfo::TriangleInfo(int vertex0, int vertex1, int vertex2)
        : vertices(vertex0, vertex1, vertex2),
          adjacentTriangles(-1, -1 ,-1),
          children(-1, -1, -1) {
    // Nop.
}

bool TriangleTreeXY::TriangleInfo::HasChildren() {
    return children.id0 != -1;
}

int TriangleTreeXY::TriangleInfo::GetVertex(int i) {
    switch (Mod3(i)) {
        case 1:
            return vertices.id1;
        case 2:
            return vertices.id2;
        default:
            return vertices.id0;
    }
}

int TriangleTreeXY::TriangleInfo::GetAdjacentTriangle(int i) {
    switch (Mod3(i)) {
        case 1:
            return adjacentTriangles.id1;
        case 2:
            return adjacentTriangles.id2;
        default:
            return adjacentTriangles.id0;
    }
}

void TriangleTreeXY::TriangleInfo::SetAdjacentTriangle(int i, int anAdjacentTriangle) {
    switch (Mod3(i)) {
        case 1:
            adjacentTriangles.id1 = anAdjacentTriangle;
            break;
        case 2:
            adjacentTriangles.id2 = anAdjacentTriangle;
            break;
        default:
            adjacentTriangles.id0 = anAdjacentTriangle;
            break;
    }
}

int TriangleTreeXY::TriangleInfo::GetChild(int i) {
    switch (i) {
        case 1:
            return children.id1;
        case 2:
            return children.id2;
        default:
            return children.id0;
    }
}

void TriangleTreeXY::TriangleInfo::AddChild(int child) {
    if (children.id0 == -1) {
        children.id0 = child;
    }
    else if (children.id1 == -1) {
        children.id1 = child;
    }
    else if (children.id2 == -1) {
        children.id2 = child;
    }
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
