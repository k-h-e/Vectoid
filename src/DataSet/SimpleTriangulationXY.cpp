#include <Vectoid/DataSet/SimpleTriangulationXY.h>

#include <K/Core/Log.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Math/Intersection/PointTriangleIntersectionXY.h>

using std::to_string;
using K::Core::Log;
using Vectoid::Core::Vector;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::BoundingBox;
using Vectoid::Math::Intersection::PointTriangleIntersectionXY;

namespace Vectoid {
namespace DataSet {

SimpleTriangulationXY::SimpleTriangulationXY()
        : vertexSet_(new VertexSet()),
          cursor_(-1) {
    // Nop.
}

void SimpleTriangulationXY::Add(const Vector<float> &point) {
    Vector<float> pointXY(point.x, point.y, 0.0f);
    vertexSet_->Add(pointXY);
    boundingBox_.Grow(pointXY);
}

bool SimpleTriangulationXY::Compute() {
    int numPoints = vertexSet_->Count();
    if (numPoints >= 3) {
        int numInserted = 0;
        triangles_.clear();
        rootTriangleIds_.clear();
        CreateRootTriangles();
        for (int i = 0; i < numPoints; ++i) {
            Log::Print(Log::Level::Debug, this, [&]{ return "point " + to_string(i); });
            const Vector<float> &point = (*vertexSet_)[i];
            int triangleId;
            if (LocateTriangleToSubdivide(point, &triangleId)) {
                SubdivideTriangle(triangleId, i);
                ++numInserted;
            }
        }

        if (numInserted == numPoints) {
            Log::Print(Log::Level::Debug, this, [&]{ return "num_triangles=" + to_string(triangles_.size()); });
            return true;
        }
    }

    triangles_.clear();
    rootTriangleIds_.clear();
    return false;
}

void SimpleTriangulationXY::PrepareToProvideTriangles() {
    cursor_ = -1;
}

bool SimpleTriangulationXY::ProvideNextTriangle(ThreePoints *outTriangle) {
    ++cursor_;
    while (cursor_ < static_cast<int>(triangles_.size())) {
        TriangleInfo &info = triangles_[cursor_];
        if (!info.numChildren) {
            outTriangle->point0 = (*vertexSet_)[info.vertexIds.id0];
            outTriangle->point1 = (*vertexSet_)[info.vertexIds.id1];
            outTriangle->point2 = (*vertexSet_)[info.vertexIds.id2];
            return true;
        }
        ++cursor_;
    }

    return false;
}

void SimpleTriangulationXY::ProvideNormal(Vector<float> *outNormal) {
    *outNormal = Vector<float>(0.0f, 1.0f, 0.0f);
}

bool SimpleTriangulationXY::TriangleError() {
    return triangles_.empty();
}

void SimpleTriangulationXY::CreateRootTriangles() {
    BoundingBox<float> box(boundingBox_);
    box.Scale(1.1f);
    Vector<float> center  = box.Center();
    Vector<float> extents = box.Extents();
    int outerVertex0 = vertexSet_->Add(Vector<float>(center.x - .5f*extents.x, center.y - .5f*extents.y, 0.0f));
    int outerVertex1 = vertexSet_->Add(Vector<float>(center.x + .5f*extents.x, center.y - .5f*extents.y, 0.0f));
    int outerVertex2 = vertexSet_->Add(Vector<float>(center.x + .5f*extents.x, center.y + .5f*extents.y, 0.0f));
    int outerVertex3 = vertexSet_->Add(Vector<float>(center.x - .5f*extents.x, center.y + .5f*extents.y, 0.0f));
    rootTriangleIds_.push_back(static_cast<int>(triangles_.size()));
    triangles_.push_back(TriangleInfo(ThreeIds(outerVertex0, outerVertex1, outerVertex2)));
    rootTriangleIds_.push_back(static_cast<int>(triangles_.size()));
    triangles_.push_back(TriangleInfo(ThreeIds(outerVertex0, outerVertex2, outerVertex3)));
}

bool SimpleTriangulationXY::LocateTriangleToSubdivide(const Vector<float> &point, int *outTriangleId) {
    for (int rootTriangleId : rootTriangleIds_) {
        int triangleId = rootTriangleId;
        bool intersects;
        if (ComputePointTriangleIntersection(point, triangleId, &intersects) && intersects) {
            while (true) {
                TriangleInfo &info = triangles_[triangleId];
                Log::Print(Log::Level::Debug, this, [&]{ return "triangle " + to_string(triangleId)
                    + " has " + to_string(info.numChildren) + " children"; });
                if (info.numChildren) {
                    if (ComputePointTriangleIntersection(point, info.children.id0, &intersects) && intersects) {
                        triangleId = info.children.id0;
                    }
                    else if ((info.numChildren >= 2)
                             && ComputePointTriangleIntersection(point, info.children.id1, &intersects) && intersects) {
                        triangleId = info.children.id1;
                    }
                    else if ((info.numChildren == 3)
                             && ComputePointTriangleIntersection(point, info.children.id2, &intersects) && intersects) {
                        triangleId = info.children.id2;
                    }
                    else {
                        return false;
                    }
                }
                else {
                    *outTriangleId = triangleId;
                    return true;
                }
            }
        }
    }
    return false;
}

bool SimpleTriangulationXY::ComputePointTriangleIntersection(const Vector<float> &point, int triangleId,
                                                             bool *outIntersects) {
    ThreeIds &vertexIds = triangles_[triangleId].vertexIds;
    ThreePoints triangle((*vertexSet_)[vertexIds.id0], (*vertexSet_)[vertexIds.id1], (*vertexSet_)[vertexIds.id2]);
    return PointTriangleIntersectionXY::Compute(point, triangle, outIntersects);
}

void SimpleTriangulationXY::SubdivideTriangle(int triangleId, int vertexId) {
    Log::Print(Log::Level::Debug, this, [&]{ return "subdividing triangle " + to_string(triangleId); });
    TriangleInfo info = triangles_[triangleId];
    info.children.id0 = static_cast<int>(triangles_.size());
    triangles_.push_back(TriangleInfo(ThreeIds(info.vertexIds.id0, info.vertexIds.id1, vertexId)));
    info.children.id1 = static_cast<int>(triangles_.size());
    triangles_.push_back(TriangleInfo(ThreeIds(info.vertexIds.id1, info.vertexIds.id2, vertexId)));
    info.children.id2 = static_cast<int>(triangles_.size());
    triangles_.push_back(TriangleInfo(ThreeIds(info.vertexIds.id2, info.vertexIds.id0, vertexId)));
    info.numChildren = 3;
    triangles_[triangleId] = info;
}

}    // Namespace DataSet.
}    // Namespace Vectoid.

