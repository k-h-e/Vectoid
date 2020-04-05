#include <Vectoid/DataSet/DelauneyTriangulationXY.h>

#include <K/Core/Log.h>
#include <K/Core/NumberTools.h>
#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Math/Intersection/PointTriangleIntersectionXY.h>
#include <Vectoid/Math/Distance/PointLineSegmentDistanceXY.h>

using std::unordered_set;
using std::deque;
using std::to_string;
using K::Core::Log;
using K::Core::NumberTools;
using Vectoid::Core::Vector;
using Vectoid::Core::TwoPoints;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::BoundingBox;
using Vectoid::Math::Intersection::PointTriangleIntersectionXY;
using Vectoid::Math::Distance::PointLineSegmentDistanceXY;

namespace Vectoid {
namespace DataSet {

DelauneyTriangulationXY::DelauneyTriangulationXY()
        : vertexSet_(new VertexSet()),
          outerTriangleVertex0Id_(-1),
          outerTriangleVertex1Id_(-1),
          outerTriangleVertex2Id_(-1),
          computed_(false),
          edgeHitEpsilon_(.01f),
          cursor_(-1),
          numEdgeHits_(0),
          numInteriorSplits_(0),
          numTrianglePairChecks_(0),
          numTrianglePairChecksRejected_(0),
          numEdgeSwaps_(0) {
    // Nop.
}

void DelauneyTriangulationXY::Add(const Vector<float> &point) {
    if (computed_) {
        vertexSet_.reset(new VertexSet());
        boundingBox_ = BoundingBox<float>();
        triangles_.clear();
        computed_ = false;
    }
    Vector<float> pointXY(point.x, point.y, 0.0f);
    vertexSet_->Add(pointXY);
    boundingBox_.Grow(pointXY);
}

bool DelauneyTriangulationXY::Compute() {
    bool success = false;

    if (!computed_ && (vertexSet_->Count() >= 3)) {
        trianglePairsToCheck_.reset(new deque<TwoIds>());
        pointQuadruplesChecked_.reset(new unordered_set<FourIdsCanonical, FourIdsCanonicalHashFunction>());
        numEdgeHits_                   = 0;
        numInteriorSplits_             = 0;
        numTrianglePairChecks_         = 0;
        numTrianglePairChecksRejected_ = 0;
        numEdgeSwaps_                  = 0;

        triangles_.clear();
        outerTriangleVertex0Id_ = -1;
        outerTriangleVertex1Id_ = -1;
        outerTriangleVertex2Id_ = -1;
        GenerateInitialOuterTriangle();
        for (int i = 0; i < vertexSet_->Count() - 3; ++i) {
            trianglePairsToCheck_->clear();
            InsertVertex(i);
            EnforceDelauneyCriterion();
        }

        Log::Print(Log::Level::Debug, this, [&]{ return "triangulation computed, num_points="
            + to_string(vertexSet_->Count() - 3) + ", num_interior_splits=" + to_string(numInteriorSplits_)
            + ", num_edge_hits=" + to_string(numEdgeHits_) + ", num_triangle_pair_checks="
            + to_string(numTrianglePairChecks_) + " (num_rejected=" + to_string(numTrianglePairChecksRejected_) + ")"
            + ", num_edge_swaps=" + to_string(numEdgeSwaps_); });
        success = true;
    }

    trianglePairsToCheck_.reset();
    pointQuadruplesChecked_.reset();
    if (!success) {
        triangles_.clear();
    }
    computed_ = true;

    return success;
}

void DelauneyTriangulationXY::PrepareToProvideTriangles() {
    cursor_ = -1;
}

bool DelauneyTriangulationXY::ProvideNextTriangle(ThreePoints *outTriangle) {
    ++cursor_;
    while (cursor_ < static_cast<int>(triangles_.size())) {
        TriangleInfo &info = triangles_[cursor_];
        if (!info.HasChildren()) {
            if (!info.vertices.Contains(outerTriangleVertex0Id_) && !info.vertices.Contains(outerTriangleVertex1Id_)
                    && !info.vertices.Contains(outerTriangleVertex2Id_)) {
                outTriangle->point0 = (*vertexSet_)[info.vertices.id0];
                outTriangle->point1 = (*vertexSet_)[info.vertices.id1];
                outTriangle->point2 = (*vertexSet_)[info.vertices.id2];
                return true;
            }
        }
        ++cursor_;
    }

    return false;
}

void DelauneyTriangulationXY::ProvideNormal(Vector<float> *outNormal) {
    *outNormal = Vector<float>(0.0f, 1.0f, 0.0f);
}

bool DelauneyTriangulationXY::TriangleError() {
    return triangles_.empty();
}

void DelauneyTriangulationXY::GenerateInitialOuterTriangle() {
    float radius = .5f * boundingBox_.Extents().Length();
    float x      = radius / std::tan(30.0f / 180.0f * (float)NumberTools::pi);
    float h      = radius / std::sin(30.0f / 180.0f * (float)NumberTools::pi);
    Vector<float> center = boundingBox_.Center();
    outerTriangleVertex0Id_ = vertexSet_->Add(Vector<float>(center.x - x, center.y - radius, 0.0f));
    outerTriangleVertex1Id_ = vertexSet_->Add(Vector<float>(center.x + x, center.y - radius, 0.0f));
    outerTriangleVertex2Id_ = vertexSet_->Add(Vector<float>(center.x, center.y + h, 0.0f));
    AddTriangle(TriangleInfo(outerTriangleVertex0Id_, outerTriangleVertex1Id_, outerTriangleVertex2Id_));
}

void DelauneyTriangulationXY::InsertVertex(int pointId) {
    Vector<float> pointToInsert = (*vertexSet_)[pointId];
    int oldTriangleId = LocateTriangle(pointToInsert, 0, pointId);
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
        if (triangles_[trianglePair.id0].HasChildren() || triangles_[trianglePair.id1].HasChildren()) {
            continue;
        }
        if (!TestDelauneyCriterion(trianglePair)) {
            PerformEdgeSwap(trianglePair);
        }
        ++numTrianglePairChecks_;
    }
}

int DelauneyTriangulationXY::LocateTriangle(const Vector<float> &point, int rootTriangleId, int locationSeqNo) {
    TriangleInfo &info = triangles_[rootTriangleId];
    if (info.lastFailedLocationSeqNo == locationSeqNo) {
        return -1;
    }
    if (info.children.id0 == -1) {    // Leaf, base case.
        ThreePoints vertices((*vertexSet_)[info.vertices.id0], (*vertexSet_)[info.vertices.id1],
                             (*vertexSet_)[info.vertices.id2]);
        bool intersects;
        if (PointTriangleIntersectionXY::Compute(point, vertices, &intersects) && intersects) {
            return rootTriangleId;
        }
    }
    else {
        for (int i = 0; i < 3; ++i) {
            int child = info.GetChild(i);
            if (child == -1) {
                break;
            }
            int triangleId = LocateTriangle(point, child, locationSeqNo);
            if (triangleId != -1) {
                return triangleId;
            }
        }

    }
    info.lastFailedLocationSeqNo = locationSeqNo;
    return -1;
}

int DelauneyTriangulationXY::TestEdgeHit(int triangleId, const Vector<float> &point) {
    TriangleInfo &info = triangles_[triangleId];
    for (int i = 0; i < 3; ++i) {
        TwoPoints edge((*vertexSet_)[info.GetVertex(i)], (*vertexSet_)[info.GetVertex(i + 1)]);
        if (PointLineSegmentDistanceXY::Compute(point, edge) <= edgeHitEpsilon_) {
            return i;
        }
    }
    return -1;
}

void DelauneyTriangulationXY::InsertPointEdgeHitCase(int oldTriangleId, int edgeId, int pointId) {
    TriangleInfo &oldTriangleInfo      = triangles_[oldTriangleId];    // Written back below.
    int          firstNewTriangleId    = static_cast<int>(triangles_.size());
    int          adjacentTriangleId    = oldTriangleInfo.GetAdjacentTriangle(edgeId);
    TriangleInfo &adjacentTriangleInfo = triangles_[adjacentTriangleId];
    int sharedEdgeAdjacentId;
    GetIdsForSharedEdge(oldTriangleId, adjacentTriangleId, &edgeId, &sharedEdgeAdjacentId);
    int newTriangle0Id = firstNewTriangleId;
    int newTriangle1Id = firstNewTriangleId + 1;
    int newTriangle2Id = firstNewTriangleId + 2;
    int newTriangle3Id = firstNewTriangleId + 3;
    int neighbor0Id    = oldTriangleInfo.GetAdjacentTriangle(Mod3(edgeId + 2));
    int neighbor1Id    = oldTriangleInfo.GetAdjacentTriangle(Mod3(edgeId + 1));
    int neighbor2Id    = adjacentTriangleInfo.GetAdjacentTriangle(Mod3(sharedEdgeAdjacentId + 2));
    int neighbor3Id    = adjacentTriangleInfo.GetAdjacentTriangle(Mod3(sharedEdgeAdjacentId + 1));

    TriangleInfo newTriangleInfo0(pointId,
                                  oldTriangleInfo.GetVertex(Mod3(edgeId + 2)),
                                  oldTriangleInfo.GetVertex(edgeId));
    newTriangleInfo0.adjacentTriangles.id0 = newTriangle1Id;
    newTriangleInfo0.adjacentTriangles.id1 = neighbor0Id;
    newTriangleInfo0.adjacentTriangles.id2 = newTriangle3Id;
    if (neighbor0Id != -1) {
        UpdateTriangleAdjacency(neighbor0Id, oldTriangleId, newTriangle0Id);
    }

    TriangleInfo newTriangleInfo1(pointId,
                                  oldTriangleInfo.GetVertex(Mod3(edgeId + 1)),
                                  oldTriangleInfo.GetVertex(Mod3(edgeId + 2)));
    newTriangleInfo1.adjacentTriangles.id0 = newTriangle2Id;
    newTriangleInfo1.adjacentTriangles.id1 = neighbor1Id;
    newTriangleInfo1.adjacentTriangles.id2 = newTriangle0Id;
    if (neighbor1Id != -1) {
        UpdateTriangleAdjacency(neighbor1Id, oldTriangleId, newTriangle1Id);
    }

    TriangleInfo newTriangleInfo2(pointId,
                                  adjacentTriangleInfo.GetVertex(Mod3(sharedEdgeAdjacentId + 2)),
                                  adjacentTriangleInfo.GetVertex(sharedEdgeAdjacentId));
    newTriangleInfo2.adjacentTriangles.id0 = newTriangle3Id;
    newTriangleInfo2.adjacentTriangles.id1 = neighbor2Id;
    newTriangleInfo2.adjacentTriangles.id2 = newTriangle1Id;
    if (neighbor2Id != -1) {
        UpdateTriangleAdjacency(neighbor2Id, adjacentTriangleId, newTriangle2Id);
    }

    TriangleInfo newTriangleInfo3(pointId,
                                  adjacentTriangleInfo.GetVertex(Mod3(sharedEdgeAdjacentId + 1)),
                                  adjacentTriangleInfo.GetVertex(Mod3(sharedEdgeAdjacentId + 2)));
    newTriangleInfo3.adjacentTriangles.id0 = newTriangle0Id;
    newTriangleInfo3.adjacentTriangles.id1 = neighbor3Id;
    newTriangleInfo3.adjacentTriangles.id2 = newTriangle2Id;
    if (neighbor3Id != -1) {
        UpdateTriangleAdjacency(neighbor3Id, adjacentTriangleId, newTriangle3Id);
    }

    oldTriangleInfo.AddChild(newTriangle0Id);
    oldTriangleInfo.AddChild(newTriangle1Id);
    adjacentTriangleInfo.AddChild(newTriangle2Id);
    adjacentTriangleInfo.AddChild(newTriangle3Id);
    AddTriangle(newTriangleInfo0);
    AddTriangle(newTriangleInfo1);
    AddTriangle(newTriangleInfo2);
    AddTriangle(newTriangleInfo3);

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
    int firstNewTriangleId = static_cast<int>(triangles_.size());
    for (int i = 0; i < 3; ++i) {
        TriangleInfo &oldTriangleInfo = triangles_[oldTriangleId];
        int adjacentTriangleId = oldTriangleInfo.GetAdjacentTriangle(i);
        if (adjacentTriangleId != -1) {
            UpdateTriangleAdjacency(adjacentTriangleId, oldTriangleId, firstNewTriangleId + i);
        }
        TriangleInfo newTriangleInfo(oldTriangleInfo.GetVertex(i), oldTriangleInfo.GetVertex(i + 1), pointId);
        newTriangleInfo.adjacentTriangles.id0 = adjacentTriangleId;
        newTriangleInfo.adjacentTriangles.id1 = firstNewTriangleId + Mod3(i + 1);
        newTriangleInfo.adjacentTriangles.id2 = firstNewTriangleId + Mod3(i + 2);
        oldTriangleInfo.AddChild(firstNewTriangleId + i);
        AddTriangle(newTriangleInfo);
        ScheduleTrianglePairCheckIfNeeded(firstNewTriangleId + i, adjacentTriangleId);
    }
    ++numInteriorSplits_;
}

// The cases where something goes wrong are treated like a passed test.
bool DelauneyTriangulationXY::TestDelauneyCriterion(const TwoIds &trianglePair) {
    TriangleInfo &triangle0 = triangles_[trianglePair.id0];
    TriangleInfo &triangle1 = triangles_[trianglePair.id1];
    int sharedEdge0Id;
    int sharedEdge1Id;
    GetIdsForSharedEdge(trianglePair.id0, trianglePair.id1, &sharedEdge0Id, &sharedEdge1Id);
    ThreePoints triangle((*vertexSet_)[triangle0.vertices.id0], (*vertexSet_)[triangle0.vertices.id1],
                         (*vertexSet_)[triangle0.vertices.id2]);
    Vector<float> fourthPoint = (*vertexSet_)[triangle1.GetVertex(Mod3(sharedEdge1Id + 2))];

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
    TriangleInfo &triangle0 = triangles_[trianglePair.id0];
    TriangleInfo &triangle1 = triangles_[trianglePair.id1];
    int sharedEdge0Id;
    int sharedEdge1Id;
    GetIdsForSharedEdge(trianglePair.id0, trianglePair.id1, &sharedEdge0Id, &sharedEdge1Id);
    int newId0 = static_cast<int>(triangles_.size());
    int newId1 = newId0 + 1;

    TriangleInfo newInfo0(triangle0.GetVertex(Mod3(sharedEdge0Id + 2)),
                          triangle1.GetVertex(Mod3(sharedEdge1Id + 2)),
                          triangle1.GetVertex(sharedEdge1Id));
    newInfo0.adjacentTriangles.id0 = newId1;
    int adjacentTriangleId = triangle1.GetAdjacentTriangle(Mod3(sharedEdge1Id + 2));
    if (adjacentTriangleId != -1) {
        UpdateTriangleAdjacency(adjacentTriangleId, trianglePair.id1, newId0);
    }
    newInfo0.adjacentTriangles.id1 = adjacentTriangleId;

    adjacentTriangleId = triangle0.GetAdjacentTriangle(Mod3(sharedEdge0Id + 1));
    if (adjacentTriangleId != -1) {
        UpdateTriangleAdjacency(adjacentTriangleId, trianglePair.id0, newId0);
    }
    newInfo0.adjacentTriangles.id2 = adjacentTriangleId;

    TriangleInfo newInfo1(triangle1.GetVertex(Mod3(sharedEdge1Id + 2)),
                          triangle0.GetVertex(Mod3(sharedEdge0Id + 2)),
                          triangle0.GetVertex(sharedEdge0Id));
    newInfo1.adjacentTriangles.id0 = newId0;
    adjacentTriangleId = triangle0.GetAdjacentTriangle(Mod3(sharedEdge0Id + 2));
    if (adjacentTriangleId != -1) {
        UpdateTriangleAdjacency(adjacentTriangleId, trianglePair.id0, newId1);
    }
    newInfo1.adjacentTriangles.id1 = adjacentTriangleId;
    adjacentTriangleId = triangle1.GetAdjacentTriangle(Mod3(sharedEdge1Id + 1));
    if (adjacentTriangleId != -1) {
        UpdateTriangleAdjacency(adjacentTriangleId, trianglePair.id1, newId1);
    }
    newInfo1.adjacentTriangles.id2 = adjacentTriangleId;

    triangle0.AddChild(newId0);
    triangle0.AddChild(newId1);
    triangle1.AddChild(newId0);
    triangle1.AddChild(newId1);
    AddTriangle(newInfo0);
    AddTriangle(newInfo1);

    ScheduleTrianglePairCheckIfNeeded(newId0, newInfo0.adjacentTriangles.id1);
    ScheduleTrianglePairCheckIfNeeded(newId0, newInfo0.adjacentTriangles.id2);
    ScheduleTrianglePairCheckIfNeeded(newId1, newInfo1.adjacentTriangles.id1);
    ScheduleTrianglePairCheckIfNeeded(newId1, newInfo1.adjacentTriangles.id2);

    ++numEdgeSwaps_;
}

void DelauneyTriangulationXY::UpdateTriangleAdjacency(int triangleToUpdateId, int oldAdjacentTriangleId,
                                                      int newAdjacentTriangleId) {
    TriangleInfo &info = triangles_[triangleToUpdateId];
    for (int i = 0; i < 3; ++i) {
        if (info.GetAdjacentTriangle(i) == oldAdjacentTriangleId) {
            info.SetAdjacentTriangle(i, newAdjacentTriangleId);
            break;
        }
    }
}

void DelauneyTriangulationXY::GetIdsForSharedEdge(int triangle0Id, int triangle1Id, int *outSharedEdge0Id,
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

void DelauneyTriangulationXY::ScheduleTrianglePairCheckIfNeeded(int triangle0Id, int triangle1Id) {
    if ((triangle0Id == -1) || (triangle1Id == -1))
        return;
    TriangleInfo &info0 = triangles_[triangle0Id];
    TriangleInfo &info1 = triangles_[triangle1Id];
    int sharedEdge0Id;
    int sharedEdge1Id;
    GetIdsForSharedEdge(triangle0Id, triangle1Id, &sharedEdge0Id, &sharedEdge1Id);
    FourIdsCanonical pointQuadruple(info0.vertices.id0, info0.vertices.id1, info0.vertices.id2,
                                    info1.GetVertex(Mod3(sharedEdge1Id + 2)));
    if (pointQuadruplesChecked_->find(pointQuadruple) == pointQuadruplesChecked_->end()) {
        trianglePairsToCheck_->push_back(TwoIds(triangle0Id, triangle1Id));
        pointQuadruplesChecked_->insert(pointQuadruple);
    }
    else {
        ++numTrianglePairChecksRejected_;
    }
}

void DelauneyTriangulationXY::AddTriangle(const TriangleInfo &info) {
    //Log::Print(Log::Level::Debug, this, [&]{ return "adding triangle " + to_string(triangles_.size())
    //    + ": (" + to_string(info.vertex0) + ", " + to_string(info.vertex1) + ", " + to_string(info.vertex2) + ")"; });
    triangles_.push_back(info);
}

int DelauneyTriangulationXY::Mod3(int value) {
    while (value > 2) {
        value -= 3;
    }
    return value;
}

DelauneyTriangulationXY::TriangleInfo::TriangleInfo(int vertex0, int vertex1, int vertex2)
        : vertices(vertex0, vertex1, vertex2),
          adjacentTriangles(-1, -1 ,-1),
          children(-1, -1, -1),
          lastFailedLocationSeqNo(-1) {
    // Nop.
}

bool DelauneyTriangulationXY::TriangleInfo::HasChildren() {
    return children.id0 != -1;
}

int DelauneyTriangulationXY::TriangleInfo::GetVertex(int i) {
    switch (Mod3(i)) {
        case 1:
            return vertices.id1;
        case 2:
            return vertices.id2;
        default:
            return vertices.id0;
    }
}

int DelauneyTriangulationXY::TriangleInfo::GetAdjacentTriangle(int i) {
    switch (Mod3(i)) {
        case 1:
            return adjacentTriangles.id1;
        case 2:
            return adjacentTriangles.id2;
        default:
            return adjacentTriangles.id0;
    }
}

void DelauneyTriangulationXY::TriangleInfo::SetAdjacentTriangle(int i, int anAdjacentTriangle) {
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

int DelauneyTriangulationXY::TriangleInfo::GetChild(int i) {
    switch (i) {
        case 1:
            return children.id1;
        case 2:
            return children.id2;
        default:
            return children.id0;
    }
}

void DelauneyTriangulationXY::TriangleInfo::AddChild(int child) {
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

