#include <K/Core/Log.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/DataSet/Triangles.h>

using std::shared_ptr;
using std::make_unique;
using std::unordered_map;
using std::to_string;
using K::Core::Log;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::Vector;
using Vectoid::DataSet::ThreeIds;
using Vectoid::DataSet::VertexSet;

namespace Vectoid {
namespace DataSet {

Triangles::Triangles(const shared_ptr<VertexSet> &vertices)
        : vertices_(vertices),
          badConnectivity_(false),
          cursor_(-1),
          currentNormal_(0.0f, 1.0f, 0.0f) {
    // Nop.
}

int Triangles::Add(const ThreePoints &triangle) {
    ThreeIds triangleVertices(vertices_->Add(triangle.point0), vertices_->Add(triangle.point1),
                              vertices_->Add(triangle.point2));
    ThreeIds edges;
    for (int i = 0; i < 3; ++i) {
        auto edge   = TwoIds(triangleVertices[i], triangleVertices[i + 1]).MakeCanonical();
        int  edgeId = -1;
        auto *edgeMap = EdgeMap();
        auto iter = edgeMap->find(edge);
        if (iter == edgeMap->end()) {
            edgeId = static_cast<int>(edges_.size());
            edges_.push_back(EdgeInfo(edge));
            (*edgeMap)[edge] = edgeId;
        } else {
            edgeId = iter->second;
        }

        edges[i] = edgeId;
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
            if (!edges_[edges[i]].AddTriangle(triangleId)) {
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

bool Triangles::BadConnectivity() {
    return badConnectivity_;
}

int Triangles::TriangleCount() {
    return static_cast<int>(triangles_.size());
}

void Triangles::GetTriangleVertices(int triangle, ThreePoints *outVertices) {
    ThreeIds &edges = triangles_[triangle];
    for (int i = 0; i < 3; ++i) {
        EdgeInfo &info0 = edges_[edges[i - 1]];
        EdgeInfo &info1 = edges_[edges[i]];
        (*outVertices)[i] = (*vertices_)[info0.vertices.SharedId(info1.vertices)];
    }
}

void Triangles::PrepareToProvideTriangles() {
    cursor_ = -1;
}

bool Triangles::ProvideNextTriangle(ThreePoints *outTriangle) {
    if (cursor_ + 1 < TriangleCount()) {
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

unordered_map<TwoIds, int, TwoIds::HashFunction> *Triangles::EdgeMap() {
    if (!edgeMap_) {
        Log::Print(Log::Level::Debug, this, []{ return "(re-)generating edge map"; });
        edgeMap_ = make_unique<unordered_map<TwoIds, int, TwoIds::HashFunction>>();
        for (int i = 0; i < static_cast<int>(edges_.size()); ++i) {
            (*edgeMap_)[edges_[i].vertices] = i;
        }
    }

    return edgeMap_.get();
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
