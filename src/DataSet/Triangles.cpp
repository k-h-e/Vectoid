#include <Vectoid/DataSet/Triangles.h>

#include <K/Core/Log.h>
#include <Vectoid/Core/BoundingBox.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/Math/Intersection/LineTriangleIntersection.h>
#include <Vectoid/DataSet/ItemIntersection.h>
#include <Vectoid/DataSet/Points.h>

using std::shared_ptr;
using std::make_shared;
using std::make_unique;
using std::unordered_map;
using std::unordered_set;
using std::to_string;
using K::Core::Log;
using Vectoid::Core::BoundingBox;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::TwoPoints;
using Vectoid::Core::Vector;
using Vectoid::Math::Intersection::LineTriangleIntersection;
using Vectoid::DataSet::LineSegments;
using Vectoid::DataSet::ThreeIds;

namespace Vectoid {
namespace DataSet {

Triangles::Triangles() : Triangles(make_shared<LineSegments>(make_shared<Points>())) {}

Triangles::Triangles(Core::TriangleProviderInterface *triangleProvider)
        : Triangles(make_shared<LineSegments>(make_shared<Points>())) {
    (void)Add(triangleProvider);
}

Triangles::Triangles(const shared_ptr<DataSet::Points> &vertices) : Triangles(make_shared<LineSegments>(vertices)) {}

Triangles::Triangles(const shared_ptr<DataSet::LineSegments> &edges)
        : vertices_(edges->Vertices()),
          edges_(edges),
          badConnectivity_(false),
          cursor_(-1),
          currentNormal_(0.0f, 1.0f, 0.0f) {
    // Nop.
}

int Triangles::Add(const ThreePoints &triangle) {
    ThreeIds edges;
    for (int i = 0; i < 3; ++i) {
        edges[i] = edges_->Add(TwoPoints(triangle[i], triangle[i + 1]));
    }

    edges = edges.MakeCanonical();
    int triangleId = -1;
    auto *triangleMap = TriangleMap();
    auto iter = triangleMap->find(edges);
    if (iter == triangleMap->end()) {
        triangleId = static_cast<int>(triangles_.size());
        triangles_.push_back(edges);
        (*triangleMap)[edges] = triangleId;
        for (int i = 0; i < 3; ++i) {
            int edge = edges[i];
            if (static_cast<int>(edgeInfos_.size()) < edge + 1) {
                edgeInfos_.resize(edge + 1);
            }
            if (!edgeInfos_[edge].AddTriangle(triangleId)) {
                badConnectivity_ = true;
                Log::Print(Log::Level::Warning, this, [&]{
                    return "bad connectivity detected, triangle=" + to_string(triangleId);
                });
            }
        }
    } else {
        triangleId = iter->second;
    }

    return triangleId;
}

bool Triangles::Add(Core::TriangleProviderInterface *triangleProvider) {
    triangleProvider->PrepareToProvideTriangles();
    ThreePoints triangle;
    while (triangleProvider->ProvideNextTriangle(&triangle)) {
        (void)Add(triangle);
    }
    return !triangleProvider->TriangleError();
}

bool Triangles::BadConnectivity() {
    return badConnectivity_;
}

void Triangles::GetTriangleVertices(int triangle, ThreePoints *outVertices) const {
    const ThreeIds &edges = triangles_[triangle];
    TwoIds vertices0, vertices1;
    for (int i = 0; i < 3; ++i) {
        edges_->GetSegmentVertices(edges[i - 1], &vertices0);
        edges_->GetSegmentVertices(edges[i],     &vertices1);
        (*outVertices)[i] = (*vertices_)[vertices0.SharedId(vertices1)];
    }
}

void Triangles::GetTriangleEdges(int triangle, ThreeIds *outEdges) {
    *outEdges = triangles_[triangle];
}

void Triangles::GetEdgeVertices(int edge, TwoIds *outVertices) {
    edges_->GetSegmentVertices(edge, outVertices);
}

int Triangles::GetNeighbor(int triangle, int edge) {
    EdgeInfo &info = edgeInfos_[edge];
    if (info.triangle0 == triangle) {
        return info.triangle1;
    } else if (info.triangle1 == triangle) {
        return info.triangle0;
    } else {
        return -1;
    }
}

unordered_set<int> Triangles::Find(const Core::Vector<float> &vertex) {
    unordered_set<int> result;

    auto num = static_cast<int>(triangles_.size());
    ThreePoints vertices;
    for (int i = 0; i < num; ++i) {
        GetTriangleVertices(i, &vertices);
        if (vertices.Contains(vertex)) {
            result.insert(i);
        }

    }

    return result;
}

void Triangles::OptimizeForSpace() {
    Log::Print(Log::Level::Debug, this, []{ return "optimizing for space"; });
    triangleMap_.reset();
    edges_->OptimizeForSpace();
}


shared_ptr<LineSegments> Triangles::Edges() {
    return edges_;
}

shared_ptr<Points> Triangles::Vertices() {
    return vertices_;
}

int Triangles::Size() const {
    return static_cast<int>(triangles_.size());
}

void Triangles::GetItemBoundingBox(int item, BoundingBox<float> *outBoundingBox) const {
    ThreePoints triangle;
    GetTriangleVertices(item, &triangle);
    *outBoundingBox = BoundingBox<float>();
    for (int i = 0; i < 3; ++i) {
        outBoundingBox->Grow(triangle[i]);
    }
}

bool Triangles::ComputeLineItemIntersection(const Vector<float> &linePoint, const Vector<float> &lineDirection,
                                            int item, bool *outIntersects, ItemIntersection *outIntersection) {
    ThreePoints triangle;
    GetTriangleVertices(item, &triangle);
    Vector<float> intersectionPoint;
    if (LineTriangleIntersection::Compute(linePoint, lineDirection, triangle, outIntersects, &intersectionPoint)) {
        if (*outIntersects) {
            *outIntersection = ItemIntersection(item, intersectionPoint);
        }
        return true;
    } else {
        return false;
    }
}

void Triangles::PrepareToProvideTriangles() {
    cursor_ = -1;
}

bool Triangles::ProvideNextTriangle(ThreePoints *outTriangle) {
    if (cursor_ + 1 < Size()) {
        ++cursor_;
        GetTriangleVertices(cursor_, outTriangle);
        outTriangle->ComputeNormal(&currentNormal_);
        if (!currentNormal_.Valid()) {
            currentNormal_ = Vector(0.0f, 1.0f, 0.0f);
        }
        return true;
    }

    return false;
}

void Triangles::ProvideNormal(Vector<float> *outNormal) {
    *outNormal = currentNormal_;
}

bool Triangles::TriangleError() {
    return false;
}

unordered_map<ThreeIds, int, ThreeIds::HashFunction> *Triangles::TriangleMap() {
    if (!triangleMap_) {
        Log::Print(Log::Level::Debug, this, []{ return "(re-)generating triangle map"; });
        triangleMap_ = make_unique<unordered_map<ThreeIds, int, ThreeIds::HashFunction>>();
        for (int i = 0; i < static_cast<int>(triangles_.size()); ++i) {
            (*triangleMap_)[triangles_[i]] = i;
        }
    }

    return triangleMap_.get();
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
