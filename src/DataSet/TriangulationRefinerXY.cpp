#include <Vectoid/DataSet/TriangulationRefinerXY.h>

#include <K/Core/Log.h>
#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/LineSegmentProviderInterface.h>
#include <Vectoid/Math/Intersection/LineSegmentLineSegmentIntersectionXY.h>
#include <Vectoid/DataSet/TriangleTreeXY.h>
#include <Vectoid/DataSet/Points.h>
#include <Vectoid/DataSet/TwoIds.h>

using std::optional;
using std::shared_ptr;
using std::to_string;
using std::unordered_set;
using K::Core::Log;
using Vectoid::Core::Vector;
using Vectoid::Core::TwoPoints;
using Vectoid::Math::Intersection::LineSegmentLineSegmentIntersectionXY;
using Vectoid::DataSet::TwoIds;

namespace Vectoid {
namespace DataSet {

TriangulationRefinerXY::TriangulationRefinerXY(const shared_ptr<TriangleTreeXY> &triangleTree,
                                               const shared_ptr<Points> &vertices)
        : triangleTree_(triangleTree),
          vertices_(vertices) {
    BuildVertexToTrianglesMap();
}

bool TriangulationRefinerXY::EnforceEdge(const TwoPoints &edge, std::vector<TwoPoints> *outRefinedEdges) {
    outRefinedEdges->clear();

    optional<int> id0 = vertices_->Id(edge.point0);
    optional<int> id1 = vertices_->Id(edge.point1);
    if (!id0 || !id1) {
        return false;
    }

    Vector<float> direction = edge.point1 - edge.point0;
    direction.Normalize();
    if (!direction.Valid()) {
        return false;
    }
    Vector<float> directionNormal(direction.y, -direction.x, 0.0f);

    int           currentVertexId = *id0;
    Vector<float> currentVertex   = edge.point0;
    while (currentVertexId != id1) {
        TwoPoints currentEdge(currentVertex, edge.point1);
        TwoIds    currentEdgeIds(currentVertexId, *id1);

        int connectingTriangleId = -1;

        for (int triangleId : vertexToTrianglesMap_[currentVertexId]) {
            TriangleTreeXY::TriangleInfo &info = (*triangleTree_)[triangleId];
            for (int i = 0; i < 3; ++i) {
                TwoIds triangleEdgeIds = info.vertices.GetEdge(i).MakeCanonical();
                if (triangleEdgeIds == currentEdgeIds.MakeCanonical()) {
                    connectingTriangleId = triangleId;
                    break;
                }
            }
            if (connectingTriangleId != -1) {
                break;
            }
        }

        if (connectingTriangleId != -1) {
            outRefinedEdges->push_back(currentEdge);
            currentVertexId = *id1;
        }
        else {
            int blockingTriangleId = -1;
            Vector<float> blockingTriangleLeftVertex;
            //int           blockingTriangleLeftEdge  = -1;
            Vector<float> blockingTriangleRightVertex;
            int           blockingTriangleRightEdge = -1;
            for (int triangleId : vertexToTrianglesMap_[currentVertexId]) {
                TriangleTreeXY::TriangleInfo &info = (*triangleTree_)[triangleId];
                bool haveLeftEdge  = false;
                bool haveRightEdge = false;
                for (int i = 0; i < 3; ++i) {
                    TwoIds triangleEdge = info.vertices.GetEdge(i);
                    if (triangleEdge.Contains(currentVertexId)) {
                        bool rightSide = (triangleEdge.id0 == currentVertexId);
                        Vector<float> otherVertex  = (*vertices_)[triangleEdge.OtherId(currentVertexId)];
                        Vector<float> triangleEdge = otherVertex - currentVertex;
                        float dotProduct = DotProduct(triangleEdge, directionNormal);
                        if (rightSide && (dotProduct >= 0)) {
                            haveRightEdge               = true;
                            blockingTriangleRightVertex = otherVertex;
                            blockingTriangleRightEdge   = i;
                        }
                        else if (!rightSide && (dotProduct <= 0)) {
                            haveLeftEdge               = true;
                            blockingTriangleLeftVertex = otherVertex;
                            //blockingTriangleLeftEdge   = i;
                        }
                    }
                }

                if (haveLeftEdge && haveRightEdge) {
                    blockingTriangleId = triangleId;
                    break;
                }
            }

            if (blockingTriangleId == -1) {
                return false;
            }

            TwoPoints edgeToSplit(blockingTriangleRightVertex, blockingTriangleLeftVertex);
            Vector<float> newVertex;
            if (!LineSegmentLineSegmentIntersectionXY::Compute(edge, edgeToSplit, &newVertex)) {
                return false;
            }
            int newVertexId = vertices_->Add(newVertex);
            Log::Print(Log::Level::Debug, this, [&]{ return "new_vertex=" + to_string(newVertexId)
                + ", distance_left=" + to_string((newVertex - blockingTriangleLeftVertex).Length())
                + ", distance_right=" + to_string((newVertex - blockingTriangleRightVertex).Length()); });

            TriangleTreeXY::TriangleInfo &blockingInfo = (*triangleTree_)[blockingTriangleId];
            int adjacentTriangleId
                = blockingInfo.GetAdjacentTriangle(TriangleTreeXY::Mod3(blockingTriangleRightEdge + 1));
            if (adjacentTriangleId == -1) {
                return false;
            }
            TriangleTreeXY::TriangleInfo &adjacentInfo = (*triangleTree_)[adjacentTriangleId];

            int edgeId;
            int sharedEdgeAdjacentId;
            triangleTree_->GetIdsForSharedEdge(blockingTriangleId, adjacentTriangleId, &edgeId, &sharedEdgeAdjacentId);

            int newTriangle0Id = triangleTree_->AddTriangle(blockingTriangleId);
            int newTriangle1Id = triangleTree_->AddTriangle(adjacentTriangleId);
            int newTriangle2Id = triangleTree_->AddTriangle(adjacentTriangleId);
            int newTriangle3Id = triangleTree_->AddTriangle(blockingTriangleId);
            int neighbor0Id    = blockingInfo.GetAdjacentTriangle(TriangleTreeXY::Mod3(edgeId + 2));
            int neighbor1Id    = adjacentInfo.GetAdjacentTriangle(TriangleTreeXY::Mod3(sharedEdgeAdjacentId + 1));
            int neighbor2Id    = adjacentInfo.GetAdjacentTriangle(TriangleTreeXY::Mod3(sharedEdgeAdjacentId + 2));
            int neighbor3Id    = blockingInfo.GetAdjacentTriangle(TriangleTreeXY::Mod3(edgeId + 1));

            TriangleTreeXY::TriangleInfo newTriangleInfo0(
                newVertexId, blockingInfo.GetVertex(TriangleTreeXY::Mod3(edgeId + 2)), blockingInfo.GetVertex(edgeId));
            newTriangleInfo0.adjacentTriangles.id0 = newTriangle3Id;
            newTriangleInfo0.adjacentTriangles.id1 = neighbor0Id;
            newTriangleInfo0.adjacentTriangles.id2 = newTriangle1Id;
            (*triangleTree_)[newTriangle0Id] = newTriangleInfo0;
            if (neighbor0Id != -1) {
                triangleTree_->UpdateTriangleAdjacency(neighbor0Id, blockingTriangleId, newTriangle0Id);
            }

            TriangleTreeXY::TriangleInfo newTriangleInfo1(
                newVertexId, adjacentInfo.GetVertex(TriangleTreeXY::Mod3(sharedEdgeAdjacentId + 1)),
                adjacentInfo.GetVertex(TriangleTreeXY::Mod3(sharedEdgeAdjacentId + 2)));
            newTriangleInfo1.adjacentTriangles.id0 = newTriangle0Id;
            newTriangleInfo1.adjacentTriangles.id1 = neighbor1Id;
            newTriangleInfo1.adjacentTriangles.id2 = newTriangle2Id;
            (*triangleTree_)[newTriangle1Id] = newTriangleInfo1;
            if (neighbor1Id != -1) {
                triangleTree_->UpdateTriangleAdjacency(neighbor1Id, adjacentTriangleId, newTriangle1Id);
            }

            TriangleTreeXY::TriangleInfo newTriangleInfo2(
                newVertexId, adjacentInfo.GetVertex(TriangleTreeXY::Mod3(sharedEdgeAdjacentId + 2)),
                adjacentInfo.GetVertex(sharedEdgeAdjacentId));
            newTriangleInfo2.adjacentTriangles.id0 = newTriangle1Id;
            newTriangleInfo2.adjacentTriangles.id1 = neighbor2Id;
            newTriangleInfo2.adjacentTriangles.id2 = newTriangle3Id;
            (*triangleTree_)[newTriangle2Id] = newTriangleInfo2;
            if (neighbor2Id != -1) {
                triangleTree_->UpdateTriangleAdjacency(neighbor2Id, adjacentTriangleId, newTriangle2Id);
            }

            TriangleTreeXY::TriangleInfo newTriangleInfo3(
                newVertexId, blockingInfo.GetVertex(TriangleTreeXY::Mod3(edgeId + 1)),
                blockingInfo.GetVertex(TriangleTreeXY::Mod3(edgeId + 2)));
            newTriangleInfo3.adjacentTriangles.id0 = newTriangle2Id;
            newTriangleInfo3.adjacentTriangles.id1 = neighbor3Id;
            newTriangleInfo3.adjacentTriangles.id2 = newTriangle0Id;
            (*triangleTree_)[newTriangle3Id] = newTriangleInfo3;
            if (neighbor3Id != -1) {
                triangleTree_->UpdateTriangleAdjacency(neighbor3Id, blockingTriangleId, newTriangle3Id);
            }

            RemoveTriangleFromVertexToTrianglesMap(blockingTriangleId);
            RemoveTriangleFromVertexToTrianglesMap(adjacentTriangleId);
            AddTriangleToVertexToTrianglesMap(newTriangle0Id);
            AddTriangleToVertexToTrianglesMap(newTriangle1Id);
            AddTriangleToVertexToTrianglesMap(newTriangle2Id);
            AddTriangleToVertexToTrianglesMap(newTriangle3Id);

            outRefinedEdges->push_back(TwoPoints(currentVertex, newVertex));
            currentVertexId = newVertexId;
            currentVertex   = newVertex;
        }
    }

    if (outRefinedEdges->size() > 1) {
        Log::Print(Log::Level::Debug, this, [&]{ return "refined edge " + edge.ToString() + " to"; });
        for (TwoPoints &segment : *outRefinedEdges) {
            Log::Print(Log::Level::Debug, this, [&]{ return "    " + segment.ToString(); });
        }
    }

    return true;
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

    boundaryCurve.PrepareToProvideLineSegments();
    TwoPoints segment;
    TwoIds    edge;
    while (boundaryCurve.ProvideNextLineSegment(&segment)) {
        optional<int> id0 = vertices_->Id(segment.point0);
        optional<int> id1 = vertices_->Id(segment.point1);
        if (!id0 || !id1) {
            Log::Print(Log::Level::Debug, this, []{ return "vertex missing"; });
            return false;
        }
        edge = TwoIds(*id0, *id1);
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
            Log::Print(Log::Level::Debug, this, [&]{ return "no triangle has edge " + edge.ToString(); });
            return false;
        }

    }
    if (boundaryEdges.empty()) {
        Log::Print(Log::Level::Debug, this, []{ return "no boundary edges"; });
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
    trianglesToProcess.insert(startTriangle);
    while (!trianglesToProcess.empty()) {
        int triangleId = *trianglesToProcess.begin();
        trianglesToProcess.erase(triangleId);
        TriangleTreeXY::TriangleInfo &info = (*triangleTree_)[triangleId];
        outSelectedTriangles->insert(triangleId);
        for (int i = 0; i < 3; ++i) {
            int adjacentTriangleId = info.GetAdjacentTriangle(i);
            if (adjacentTriangleId != -1) {
                if (boundaryEdges.find(info.vertices.GetEdge(i).MakeCanonical()) == boundaryEdges.end()) {
                    if (outSelectedTriangles->find(adjacentTriangleId) == outSelectedTriangles->end()) {
                        trianglesToProcess.insert(adjacentTriangleId);
                    }
                }
            }
        }
    }

    return true;
}

void TriangulationRefinerXY::BuildVertexToTrianglesMap() {
    vertexToTrianglesMap_.clear();
    for (int triangleId = 0; triangleId < triangleTree_->Count(); ++triangleId) {
        AddTriangleToVertexToTrianglesMap(triangleId);
    }
}

void TriangulationRefinerXY::AddTriangleToVertexToTrianglesMap(int triangleId) {
    TriangleTreeXY::TriangleInfo &info = (*triangleTree_)[triangleId];
    if (!info.HasChildren()) {
        for (int i = 0; i < 3; ++i) {
            int vertexId = info.vertices[i];
            vertexToTrianglesMap_[vertexId].insert(triangleId);
        }
    }
}

void TriangulationRefinerXY::RemoveTriangleFromVertexToTrianglesMap(int triangleId) {
    TriangleTreeXY::TriangleInfo &info = (*triangleTree_)[triangleId];
    for (int i = 0; i < 3; ++i) {
        int vertexId = info.vertices[i];
        vertexToTrianglesMap_[vertexId].erase(triangleId);
    }
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
