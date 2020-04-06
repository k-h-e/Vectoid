#include <Vectoid/DataSet/TriangulationRefinerXY.h>

#include <K/Core/Log.h>
#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/LineSegmentProviderInterface.h>
#include <Vectoid/DataSet/TriangleTreeXY.h>
#include <Vectoid/DataSet/VertexSet.h>
#include <Vectoid/DataSet/TwoIds.h>

using std::shared_ptr;
using std::unordered_set;
using K::Core::Log;
using Vectoid::Core::TwoPoints;
using Vectoid::DataSet::TwoIds;

namespace Vectoid {
namespace DataSet {

TriangulationRefinerXY::TriangulationRefinerXY(const shared_ptr<TriangleTreeXY> &triangleTree,
                                               const shared_ptr<VertexSet> &vertexSet)
        : triangleTree_(triangleTree),
          vertexSet_(vertexSet) {
    BuildVertexToTrianglesMap();
}

bool TriangulationRefinerXY::SelectSurface(Core::LineSegmentProviderInterface &boundaryCurve,
                                           unordered_set<int> *outSelectedTriangles) {
    Log::Print(Log::Level::Debug, this, []{ return "selecting surface..."; });
    outSelectedTriangles->clear();

    struct TwoIdsHash {
        std::size_t operator()(const TwoIds &twoIds) const {
            return twoIds.Hash();
        }
    };
    std::unordered_set<TwoIds, TwoIdsHash> boundaryEdges;

    int numBadEdges = 0;
    boundaryCurve.PrepareToProvideLineSegments();
    TwoPoints segment;
    TwoIds    edge;
    while (boundaryCurve.ProvideNextLineSegment(&segment)) {
        int id0 = vertexSet_->GetId(segment.point0);
        int id1 = vertexSet_->GetId(segment.point1);
        if ((id0 == -1) || (id1 == -1)) {
            return false;
        }
        edge = TwoIds(id0, id1);
        boundaryEdges.insert(edge.MakeCanonical());

        bool haveTriangle = false;
        for (int triangleId : vertexToTrianglesMap_[edge.id0]) {
            TriangleTreeXY::TriangleInfo &info = (*triangleTree_)[triangleId];
            for (int i = 0; i < 3; ++i) {
                if (info.vertices.GetEdge(i).MakeCanonical() == edge.MakeCanonical()) {
                    haveTriangle = true;
                }
            }
        }
        if (!haveTriangle) {
            numBadEdges++;
        }

    }
    if (boundaryEdges.empty()) {
        return false;
    }

    Log::Print(Log::Level::Debug, this, [&]{ return "bad_edges=" + to_string(numBadEdges); });
    if (numBadEdges) {
        return false;
    }

    int startTriangle = -1;
    for (int triangleId : vertexToTrianglesMap_[edge.id0]) {
        TriangleTreeXY::TriangleInfo &info = (*triangleTree_)[triangleId];
        for (int i = 0; i < 3; ++i) {
            if (info.vertices.GetEdge(i) == edge) {
                startTriangle = triangleId;
                break;
            }
        }
    }

    Log::Print(Log::Level::Debug, this, [&]{ return "start_triangle=" + to_string(startTriangle); });
    unordered_set<int> trianglesToProcess;
    unordered_set<int> rejectedTriangles;
    trianglesToProcess.insert(startTriangle);
    while (!trianglesToProcess.empty()) {
        Log::Print(Log::Level::Debug, this, [&]{ return "selected=" + to_string(outSelectedTriangles->size())
            + ", to_process=" + to_string(trianglesToProcess.size()); });
        int triangleId = *trianglesToProcess.begin();
        trianglesToProcess.erase(triangleId);
        TriangleTreeXY::TriangleInfo &info = (*triangleTree_)[triangleId];
        if (!info.HasChildren()) {
            outSelectedTriangles->insert(triangleId);
            for (int i = 0; i < 3; ++i) {
                int adjacentTriangleId = info.GetAdjacentTriangle(i);
                if (adjacentTriangleId != -1) {
                    if (boundaryEdges.find(info.vertices.GetEdge(i).MakeCanonical()) == boundaryEdges.end()) {
                        if (outSelectedTriangles->find(adjacentTriangleId) == outSelectedTriangles->end()) {
                            if (rejectedTriangles.find(adjacentTriangleId) == rejectedTriangles.end()) {
                                trianglesToProcess.insert(adjacentTriangleId);
                            }
                        }
                    }
                }
            }
        }
        else {
            rejectedTriangles.insert(triangleId);
        }

        if (outSelectedTriangles->size() == 450u) {
            break;
        }
    }

    return true;
}

void TriangulationRefinerXY::BuildVertexToTrianglesMap() {
    vertexToTrianglesMap_.clear();
    for (int triangleId = 0; triangleId < triangleTree_->Count(); ++triangleId) {
        TriangleTreeXY::TriangleInfo &info = (*triangleTree_)[triangleId];
        if (!info.HasChildren()) {
            for (int i = 0; i < 3; ++i) {
                int vertexId = info.vertices[i];
                vertexToTrianglesMap_[vertexId].insert(triangleId);
            }
        }
    }
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
