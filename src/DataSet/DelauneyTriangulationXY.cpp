#include <Vectoid/DataSet/DelauneyTriangulationXY.h>

#include <K/Core/Log.h>
#include <K/Core/NumberTools.h>
#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Math/Distance/PointLineSegmentDistanceXY.h>
#include <Vectoid/DataSet/TriangleTreeXY.h>

using std::shared_ptr;
using std::unordered_set;
using std::deque;
using std::to_string;
using K::Core::Log;
using K::Core::NumberTools;
using Vectoid::Core::Vector;
using Vectoid::Core::TwoPoints;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::BoundingBox;
using Vectoid::Math::Distance::PointLineSegmentDistanceXY;

namespace Vectoid {
namespace DataSet {

DelauneyTriangulationXY::DelauneyTriangulationXY() {
    Reset();
}

void DelauneyTriangulationXY::Add(const Vector<float> &point) {
    if (computed_) {
        Reset();
    }
    Vector<float> pointXY(point.x, point.y, 0.0f);
    vertices_->Add(pointXY);
    boundingBox_.Grow(pointXY);
}

bool DelauneyTriangulationXY::Compute() {
    bool success = false;

    if (!computed_ && (vertices_->Count() >= 3)) {
        trianglePairsToCheck_.reset(new deque<TwoIds>());
        pointQuadruplesChecked_.reset(new unordered_set<FourIdsCanonical, FourIdsCanonicalHashFunction>());
        GenerateInitialOuterTriangle();
        for (int i = 0; i < vertices_->Count() - 3; ++i) {
            trianglePairsToCheck_->clear();
            InsertVertex(i);
            EnforceDelauneyCriterion();
        }

        Log::Print(Log::Level::Debug, this, [&]{ return "triangulation computed, num_points="
            + to_string(vertices_->Count() - 3) + ", num_interior_splits=" + to_string(numInteriorSplits_)
            + ", num_edge_hits=" + to_string(numEdgeHits_) + ", num_triangle_pair_checks="
            + to_string(numTrianglePairChecks_) + " (num_rejected=" + to_string(numTrianglePairChecksRejected_) + ")"
            + ", num_edge_swaps=" + to_string(numEdgeSwaps_); });
        success = true;
    }

    trianglePairsToCheck_.reset();
    pointQuadruplesChecked_.reset();
    if (!success) {
        Reset();
    }
    computationSuccessful_ = success;
    computed_              = true;
    return success;
}

bool DelauneyTriangulationXY::Reap(shared_ptr<TriangleTreeXY> *outTriangleTree, shared_ptr<Points> *outVertices,
                                   ThreeIds *outOuterTriangle) {
    bool success = false;

    if (computed_ && computationSuccessful_) {
        *outTriangleTree  = triangleTree_;
        *outVertices      = vertices_;
        *outOuterTriangle = ThreeIds(outerTriangleVertex0Id_, outerTriangleVertex1Id_, outerTriangleVertex2Id_);
        success = true;
    }

    Reset();

    if (!success) {
        outTriangleTree->reset();
        outVertices->reset();
    }
    return success;
}

void DelauneyTriangulationXY::PrepareToProvideTriangles() {
    triangleTree_->PrepareToProvideTriangles();
}

bool DelauneyTriangulationXY::ProvideNextTriangle(ThreePoints *outTriangle) {
    while (triangleTree_->ProvideNextTriangle(outTriangle)) {
        if (!outTriangle->Contains((*vertices_)[outerTriangleVertex0Id_])
                && !outTriangle->Contains((*vertices_)[outerTriangleVertex1Id_])
                && !outTriangle->Contains((*vertices_)[outerTriangleVertex2Id_])) {
            return true;
        }
    }

    return false;
}

void DelauneyTriangulationXY::ProvideNormal(Vector<float> *outNormal) {
    triangleTree_->ProvideNormal(outNormal);
}

bool DelauneyTriangulationXY::TriangleError() {
    return triangleTree_->TriangleError();
}

void DelauneyTriangulationXY::Reset() {
    vertices_.reset(new Points());
    boundingBox_ = BoundingBox<float>();
    triangleTree_.reset(new TriangleTreeXY(vertices_));
    outerTriangleVertex0Id_ = -1;
    outerTriangleVertex1Id_ = -1;
    outerTriangleVertex2Id_ = -1;
    computed_               = false;
    computationSuccessful_  = false;
    edgeHitEpsilon_         = .01f;

    numEdgeHits_                   = 0;
    numInteriorSplits_             = 0;
    numTrianglePairChecks_         = 0;
    numTrianglePairChecksRejected_ = 0;
    numEdgeSwaps_                  = 0;

    trianglePairsToCheck_.reset();
    pointQuadruplesChecked_.reset();
}

void DelauneyTriangulationXY::GenerateInitialOuterTriangle() {
    float radius = .5f * boundingBox_.Extents().Length();
    radius *= 1.01f;
    float x      = radius / std::tan(30.0f / 180.0f * (float)NumberTools::pi);
    float h      = radius / std::sin(30.0f / 180.0f * (float)NumberTools::pi);
    Vector<float> center = boundingBox_.Center();
    outerTriangleVertex0Id_ = vertices_->Add(Vector<float>(center.x - x, center.y - radius, 0.0f));
    outerTriangleVertex1Id_ = vertices_->Add(Vector<float>(center.x + x, center.y - radius, 0.0f));
    outerTriangleVertex2Id_ = vertices_->Add(Vector<float>(center.x, center.y + h, 0.0f));
    int triangleId = triangleTree_->AddTriangle(-1);
    (*triangleTree_)[triangleId] = TriangleTreeXY::TriangleInfo(outerTriangleVertex0Id_, outerTriangleVertex1Id_,
                                                                outerTriangleVertex2Id_);
}

void DelauneyTriangulationXY::InsertVertex(int pointId) {
    Vector<float> pointToInsert = (*vertices_)[pointId];
    int oldTriangleId = triangleTree_->LocateTriangle(pointToInsert, 0);
    if (oldTriangleId == -1) {
        Log::Print(Log::Level::Debug, this, [&]{ return "can't insert point " + to_string(pointId)
            + ", did not find containing triangle"; });
        return;
    }

    int edgeId = TestEdgeHit(oldTriangleId, pointToInsert);
    if (edgeId != -1) {
        InsertPointEdgeHitCase(oldTriangleId, edgeId, pointId);
    }
    else {
        InsertPointInteriorCase(oldTriangleId, pointId);
    }
}

void DelauneyTriangulationXY::EnforceDelauneyCriterion() {
    while (!trianglePairsToCheck_->empty()) {
        TwoIds trianglePair = trianglePairsToCheck_->front();
        trianglePairsToCheck_->pop_front();
        if ((*triangleTree_)[trianglePair.id0].HasChildren() || (*triangleTree_)[trianglePair.id1].HasChildren()) {
            continue;
        }
        if (!TestDelauneyCriterion(trianglePair)) {
            PerformEdgeSwap(trianglePair);
        }
        ++numTrianglePairChecks_;
    }
}

int DelauneyTriangulationXY::TestEdgeHit(int triangleId, const Vector<float> &point) {
    TriangleTreeXY::TriangleInfo &info = (*triangleTree_)[triangleId];
    for (int i = 0; i < 3; ++i) {
        TwoPoints edge((*vertices_)[info.GetVertex(i)], (*vertices_)[info.GetVertex(i + 1)]);
        if (PointLineSegmentDistanceXY::Compute(point, edge) <= edgeHitEpsilon_) {
            return i;
        }
    }
    return -1;
}

void DelauneyTriangulationXY::InsertPointEdgeHitCase(int oldTriangleId, int edgeId, int pointId) {
    TriangleTreeXY::TriangleInfo &oldTriangleInfo      = (*triangleTree_)[oldTriangleId];    // Written back below.
    int                          adjacentTriangleId    = oldTriangleInfo.GetAdjacentTriangle(edgeId);
    TriangleTreeXY::TriangleInfo &adjacentTriangleInfo = (*triangleTree_)[adjacentTriangleId];
    int sharedEdgeAdjacentId;
    triangleTree_->GetIdsForSharedEdge(oldTriangleId, adjacentTriangleId, &edgeId, &sharedEdgeAdjacentId);

    int newTriangle0Id = triangleTree_->AddTriangle(oldTriangleId);
    int newTriangle1Id = triangleTree_->AddTriangle(oldTriangleId);
    int newTriangle2Id = triangleTree_->AddTriangle(adjacentTriangleId);
    int newTriangle3Id = triangleTree_->AddTriangle(adjacentTriangleId);
    int neighbor0Id    = oldTriangleInfo.GetAdjacentTriangle(TriangleTreeXY::Mod3(edgeId + 2));
    int neighbor1Id    = oldTriangleInfo.GetAdjacentTriangle(TriangleTreeXY::Mod3(edgeId + 1));
    int neighbor2Id    = adjacentTriangleInfo.GetAdjacentTriangle(TriangleTreeXY::Mod3(sharedEdgeAdjacentId + 2));
    int neighbor3Id    = adjacentTriangleInfo.GetAdjacentTriangle(TriangleTreeXY::Mod3(sharedEdgeAdjacentId + 1));

    TriangleTreeXY::TriangleInfo newTriangleInfo0(
        pointId, oldTriangleInfo.GetVertex(TriangleTreeXY::Mod3(edgeId + 2)), oldTriangleInfo.GetVertex(edgeId));
    newTriangleInfo0.adjacentTriangles.id0 = newTriangle1Id;
    newTriangleInfo0.adjacentTriangles.id1 = neighbor0Id;
    newTriangleInfo0.adjacentTriangles.id2 = newTriangle3Id;
    (*triangleTree_)[newTriangle0Id] = newTriangleInfo0;
    if (neighbor0Id != -1) {
        triangleTree_->UpdateTriangleAdjacency(neighbor0Id, oldTriangleId, newTriangle0Id);
    }

    TriangleTreeXY::TriangleInfo newTriangleInfo1(
        pointId, oldTriangleInfo.GetVertex(TriangleTreeXY::Mod3(edgeId + 1)),
        oldTriangleInfo.GetVertex(TriangleTreeXY::Mod3(edgeId + 2)));
    newTriangleInfo1.adjacentTriangles.id0 = newTriangle2Id;
    newTriangleInfo1.adjacentTriangles.id1 = neighbor1Id;
    newTriangleInfo1.adjacentTriangles.id2 = newTriangle0Id;
    (*triangleTree_)[newTriangle1Id] = newTriangleInfo1;
    if (neighbor1Id != -1) {
        triangleTree_->UpdateTriangleAdjacency(neighbor1Id, oldTriangleId, newTriangle1Id);
    }

    TriangleTreeXY::TriangleInfo newTriangleInfo2(
        pointId, adjacentTriangleInfo.GetVertex(TriangleTreeXY::Mod3(sharedEdgeAdjacentId + 2)),
        adjacentTriangleInfo.GetVertex(sharedEdgeAdjacentId));
    newTriangleInfo2.adjacentTriangles.id0 = newTriangle3Id;
    newTriangleInfo2.adjacentTriangles.id1 = neighbor2Id;
    newTriangleInfo2.adjacentTriangles.id2 = newTriangle1Id;
    (*triangleTree_)[newTriangle2Id] = newTriangleInfo2;
    if (neighbor2Id != -1) {
        triangleTree_->UpdateTriangleAdjacency(neighbor2Id, adjacentTriangleId, newTriangle2Id);
    }

    TriangleTreeXY::TriangleInfo newTriangleInfo3(
        pointId, adjacentTriangleInfo.GetVertex(TriangleTreeXY::Mod3(sharedEdgeAdjacentId + 1)),
        adjacentTriangleInfo.GetVertex(TriangleTreeXY::Mod3(sharedEdgeAdjacentId + 2)));
    newTriangleInfo3.adjacentTriangles.id0 = newTriangle0Id;
    newTriangleInfo3.adjacentTriangles.id1 = neighbor3Id;
    newTriangleInfo3.adjacentTriangles.id2 = newTriangle2Id;
    (*triangleTree_)[newTriangle3Id] = newTriangleInfo3;
    if (neighbor3Id != -1) {
        triangleTree_->UpdateTriangleAdjacency(neighbor3Id, adjacentTriangleId, newTriangle3Id);
    }

    ScheduleTrianglePairCheckIfNeeded(newTriangle0Id, newTriangle1Id);
    ScheduleTrianglePairCheckIfNeeded(newTriangle1Id, newTriangle2Id);
    ScheduleTrianglePairCheckIfNeeded(newTriangle2Id, newTriangle3Id);
    ScheduleTrianglePairCheckIfNeeded(newTriangle3Id, newTriangle0Id);
    ScheduleTrianglePairCheckIfNeeded(newTriangle0Id, neighbor0Id);
    ScheduleTrianglePairCheckIfNeeded(newTriangle1Id, neighbor1Id);
    ScheduleTrianglePairCheckIfNeeded(newTriangle2Id, neighbor2Id);
    ScheduleTrianglePairCheckIfNeeded(newTriangle3Id, neighbor3Id);

    ++numEdgeHits_;
}

void DelauneyTriangulationXY::InsertPointInteriorCase(int oldTriangleId, int pointId) {
    int newTriangleIds[3];
    for (int i = 0; i < 3; ++i) {
        newTriangleIds[i] = triangleTree_->AddTriangle(oldTriangleId);
    }
    for (int i = 0; i < 3; ++i) {
        TriangleTreeXY::TriangleInfo &oldTriangleInfo = (*triangleTree_)[oldTriangleId];
        int adjacentTriangleId = oldTriangleInfo.GetAdjacentTriangle(i);
        if (adjacentTriangleId != -1) {
            triangleTree_->UpdateTriangleAdjacency(adjacentTriangleId, oldTriangleId, newTriangleIds[i]);
        }
        TriangleTreeXY::TriangleInfo newTriangleInfo(
            oldTriangleInfo.GetVertex(i), oldTriangleInfo.GetVertex(i + 1), pointId);
        newTriangleInfo.adjacentTriangles.id0 = adjacentTriangleId;
        newTriangleInfo.adjacentTriangles.id1 = newTriangleIds[TriangleTreeXY::Mod3(i + 1)];
        newTriangleInfo.adjacentTriangles.id2 = newTriangleIds[TriangleTreeXY::Mod3(i + 2)];
        (*triangleTree_)[newTriangleIds[i]] = newTriangleInfo;
        ScheduleTrianglePairCheckIfNeeded(newTriangleIds[i], adjacentTriangleId);
    }
    ++numInteriorSplits_;
}

// The cases where something goes wrong are treated like a passed test.
bool DelauneyTriangulationXY::TestDelauneyCriterion(const TwoIds &trianglePair) {
    TriangleTreeXY::TriangleInfo &triangle0 = (*triangleTree_)[trianglePair.id0];
    TriangleTreeXY::TriangleInfo &triangle1 = (*triangleTree_)[trianglePair.id1];
    int sharedEdge0Id;
    int sharedEdge1Id;
    triangleTree_->GetIdsForSharedEdge(trianglePair.id0, trianglePair.id1, &sharedEdge0Id, &sharedEdge1Id);
    ThreePoints triangle((*vertices_)[triangle0.vertices.id0], (*vertices_)[triangle0.vertices.id1],
                         (*vertices_)[triangle0.vertices.id2]);
    Vector<float> fourthPoint = (*vertices_)[triangle1.GetVertex(TriangleTreeXY::Mod3(sharedEdge1Id + 2))];

    Vector<float> base0 = .5f*triangle.point0 + .5f*triangle.point1;
    Vector<float> dir0  = triangle.point1 - triangle.point0;
    Vector<float> base1 = .5f*triangle.point1 + .5f*triangle.point2;
    Vector<float> dir1  = triangle.point2 - triangle.point1;
    dir0 = Vector<float>(-dir0.y, dir0.x, 0.0f);
    dir1 = Vector<float>(-dir1.y, dir1.x, 0.0f);
    dir0.Normalize();
    if (!dir0.Valid()) {
        Log::Print(Log::Level::Debug, this, []{ return "failed to normalize dir0"; });
        return true;
    }
    dir1.Normalize();
    if (!dir1.Valid()) {
        Log::Print(Log::Level::Debug, this, []{ return "failed to normalize dir1"; });
        return true;
    }
    Vector<float> normal0(-dir0.y, dir0.x, 0.0f);
    float distance = DotProduct(base1 - base0, normal0);
    float step     = DotProduct(dir1, normal0);
    if (step == 0.0f) {
        Log::Print(Log::Level::Debug, this, []{ return "step is 0"; });
        return true;
    }
    float         k            = distance / step;
    Vector<float> center       = base1 - k*dir1;
    float         radius       = (triangle.point0 - center).LengthXY();
    float         fourthPointDistance = (fourthPoint - center).LengthXY();

    return (fourthPointDistance > radius);
}

void DelauneyTriangulationXY::PerformEdgeSwap(const TwoIds &trianglePair) {
    int newId0 = triangleTree_->AddTriangle(trianglePair.id0);
    int newId1 = triangleTree_->AddTriangle(trianglePair.id0);
    TriangleTreeXY::TriangleInfo &triangle0 = (*triangleTree_)[trianglePair.id0];
    TriangleTreeXY::TriangleInfo &triangle1 = (*triangleTree_)[trianglePair.id1];
    int sharedEdge0Id;
    int sharedEdge1Id;
    triangleTree_->GetIdsForSharedEdge(trianglePair.id0, trianglePair.id1, &sharedEdge0Id, &sharedEdge1Id);

    TriangleTreeXY::TriangleInfo newInfo0(
        triangle0.GetVertex(TriangleTreeXY::Mod3(sharedEdge0Id + 2)),
        triangle1.GetVertex(TriangleTreeXY::Mod3(sharedEdge1Id + 2)), triangle1.GetVertex(sharedEdge1Id));
    newInfo0.adjacentTriangles.id0 = newId1;
    int adjacentTriangleId = triangle1.GetAdjacentTriangle(TriangleTreeXY::Mod3(sharedEdge1Id + 2));
    if (adjacentTriangleId != -1) {
        triangleTree_->UpdateTriangleAdjacency(adjacentTriangleId, trianglePair.id1, newId0);
    }
    newInfo0.adjacentTriangles.id1 = adjacentTriangleId;
    adjacentTriangleId = triangle0.GetAdjacentTriangle(TriangleTreeXY::Mod3(sharedEdge0Id + 1));
    if (adjacentTriangleId != -1) {
        triangleTree_->UpdateTriangleAdjacency(adjacentTriangleId, trianglePair.id0, newId0);
    }
    newInfo0.adjacentTriangles.id2 = adjacentTriangleId;
    (*triangleTree_)[newId0] = newInfo0;

    TriangleTreeXY::TriangleInfo newInfo1(
        triangle1.GetVertex(TriangleTreeXY::Mod3(sharedEdge1Id + 2)),
        triangle0.GetVertex(TriangleTreeXY::Mod3(sharedEdge0Id + 2)), triangle0.GetVertex(sharedEdge0Id));
    newInfo1.adjacentTriangles.id0 = newId0;
    adjacentTriangleId = triangle0.GetAdjacentTriangle(TriangleTreeXY::Mod3(sharedEdge0Id + 2));
    if (adjacentTriangleId != -1) {
        triangleTree_->UpdateTriangleAdjacency(adjacentTriangleId, trianglePair.id0, newId1);
    }
    newInfo1.adjacentTriangles.id1 = adjacentTriangleId;
    adjacentTriangleId = triangle1.GetAdjacentTriangle(TriangleTreeXY::Mod3(sharedEdge1Id + 1));
    if (adjacentTriangleId != -1) {
        triangleTree_->UpdateTriangleAdjacency(adjacentTriangleId, trianglePair.id1, newId1);
    }
    newInfo1.adjacentTriangles.id2 = adjacentTriangleId;
    (*triangleTree_)[newId1] = newInfo1;

    (*triangleTree_)[trianglePair.id1].AddChild(newId0);
    (*triangleTree_)[trianglePair.id1].AddChild(newId1);
    // The two new triangles were also added as children of trianglePair.id0 above!

    ScheduleTrianglePairCheckIfNeeded(newId0, newInfo0.adjacentTriangles.id1);
    ScheduleTrianglePairCheckIfNeeded(newId0, newInfo0.adjacentTriangles.id2);
    ScheduleTrianglePairCheckIfNeeded(newId1, newInfo1.adjacentTriangles.id1);
    ScheduleTrianglePairCheckIfNeeded(newId1, newInfo1.adjacentTriangles.id2);

    ++numEdgeSwaps_;
}

void DelauneyTriangulationXY::ScheduleTrianglePairCheckIfNeeded(int triangle0Id, int triangle1Id) {
    if ((triangle0Id == -1) || (triangle1Id == -1)) {
        return;
    }
    TriangleTreeXY::TriangleInfo &info0 = (*triangleTree_)[triangle0Id];
    TriangleTreeXY::TriangleInfo &info1 = (*triangleTree_)[triangle1Id];
    int sharedEdge0Id;
    int sharedEdge1Id;
    triangleTree_->GetIdsForSharedEdge(triangle0Id, triangle1Id, &sharedEdge0Id, &sharedEdge1Id);
    FourIdsCanonical pointQuadruple(info0.vertices.id0, info0.vertices.id1, info0.vertices.id2,
                                    info1.GetVertex(TriangleTreeXY::Mod3(sharedEdge1Id + 2)));
    if (pointQuadruplesChecked_->find(pointQuadruple) == pointQuadruplesChecked_->end()) {
        trianglePairsToCheck_->push_back(TwoIds(triangle0Id, triangle1Id));
        pointQuadruplesChecked_->insert(pointQuadruple);
    }
    else {
        ++numTrianglePairChecksRejected_;
    }
}

DelauneyTriangulationXY::FourIdsCanonical::FourIdsCanonical(int anId0, int anId1, int anId2, int anId3) {
    id0 = anId0;
    id1 = anId1;
    id2 = anId2;
    id3 = anId3;

    if (id1 < id0) {
        NumberTools::Swap(&id0, &id1);
    }
    if (id2 < id0) {
        NumberTools::Swap(&id0, &id2);
    }
    if (id3 < id0) {
        NumberTools::Swap(&id0, &id3);
    }

    if (id2 < id1) {
        NumberTools::Swap(&id1, &id2);
    }
    if (id3 < id1) {
        NumberTools::Swap(&id1, &id3);
    }

    if (id3 < id2) {
        NumberTools::Swap(&id2, &id3);
    }
}

bool DelauneyTriangulationXY::FourIdsCanonical::operator==(const FourIdsCanonical &other) const {
    return (id0 == other.id0) && (id1 == other.id1) && (id2 == other.id2) && (id3 == other.id3);
}

std::size_t DelauneyTriangulationXY::FourIdsCanonical::Hash() const {
    std::size_t hash = 17u;
    hash = hash*31u + std::hash<int>()(id0);
    hash = hash*31u + std::hash<int>()(id1);
    hash = hash*31u + std::hash<int>()(id2);
    hash = hash*31u + std::hash<int>()(id3);
    return hash;
}

}    // Namespace DataSet.
}    // Namespace Vectoid.

