#ifndef VECTOID_DATASET_DELAUNEYTRIANGULATIONXY_H_
#define VECTOID_DATASET_DELAUNEYTRIANGULATIONXY_H_

#include <memory>
#include <deque>
#include <unordered_set>
#include <Vectoid/Core/BoundingBox.h>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/DataSet/VertexSet.h>
#include <Vectoid/DataSet/TwoIds.h>
#include <Vectoid/DataSet/ThreeIds.h>

namespace Vectoid {
namespace DataSet {

//! Generates a Delauney triangulation for a set of vertices in the <c>x/y</c>-plane.
/*!
 *  \ingroup Vectoid
 */
class DelauneyTriangulationXY : public virtual Core::TriangleProviderInterface {
  public:
    DelauneyTriangulationXY();
    DelauneyTriangulationXY(const DelauneyTriangulationXY &other)             = delete;
    DelauneyTriangulationXY &operator=(const DelauneyTriangulationXY &other)  = delete;
    DelauneyTriangulationXY(const DelauneyTriangulationXY &&other)            = delete;
    DelauneyTriangulationXY &operator=(const DelauneyTriangulationXY &&other) = delete;

    //! Adds the specified point in the <c>x/y</c>-plane (<c>z</c> coordinate will be zeroed).
    /*!
     *  The first call to this method after a triangulation has been computed resets the object for a new computation
     *  (before adding the vertex).
     */
    void Add(const Core::Vector<float> &point);
    //! Computes the triangulation.
    /*!
     *  \return
     *  <c>false</c> in case of failure. The triangulation will then be empty.
     */
    bool Compute();

    virtual void PrepareToProvideTriangles();
    virtual bool ProvideNextTriangle(Core::ThreePoints *outTriangle);
    virtual void ProvideNormal(Core::Vector<float> *outNormal);
    virtual bool TriangleError();

  private:
    struct TriangleInfo {
        // Counter-clockwise ordering...
        ThreeIds vertices;

        // Adjacent triangle n shares the edge (vertex_n, vertex_n+1). Id -1 is special and means "no adjacent triangle
        // sharing this edge"...
        ThreeIds adjacentTriangles;

        // Id -1 is special and means "this child is not present". If a triangle has n children, then these will be
        // referenced by child_0, ..., child_n-1...
        ThreeIds children;

        int lastFailedLocationSeqNo;

        TriangleInfo(int vertex0, int vertex1, int vertex2);
        // Default copy/move, ok.

        bool HasChildren();
        //! Returns the vertex for the specified index, which must be non-negative (modulo <c>3</c> for <c>i</c> in
        //! <c>{3, 4, 5}</c> will get applied).
        int GetVertex(int i);
        //! Returns the adjacent triangle for the specified index, which must be non-negative (modulo <c>3</c> for
        //! <c>i</c> in <c>{3, 4, 5}</c> will get applied).
        int GetAdjacentTriangle(int i);
        //! Sets the adjacent triangle for the specified index, which must be non-negative (modulo <c>3</c> for
        //! <c>i</c> in <c>{3, 4, 5}</c> will get applied).
        void SetAdjacentTriangle(int i, int anAdjacentTriangle);
        int GetChild(int i);
        void AddChild(int child);
    };

    struct FourIdsCanonical {
        int id0;
        int id1;
        int id2;
        int id3;

        FourIdsCanonical(int anId0, int anId1, int anId2, int anId3);
        // Default copy/move, ok.

        bool operator==(const FourIdsCanonical &other) const;
        std::size_t Hash() const;
    };
    struct FourIdsCanonicalHashFunction {
        std::size_t operator()(const FourIdsCanonical &ids) const {
            return ids.Hash();
        }
    };

    void GenerateInitialOuterTriangle();
    void InsertVertex(int pointId);
    void EnforceDelauneyCriterion();
    int LocateTriangle(const Core::Vector<float> &point, int rootTriangleId, int locationSeqNo);
    int TestEdgeHit(int triangleId, const Core::Vector<float> &point);
    void InsertPointEdgeHitCase(int oldTriangleId, int edgeId, int pointId);
    void InsertPointInteriorCase(int oldTriangleId, int pointId);
    void GetIdsForSharedEdge(int triangle0Id, int triangle1Id, int *outSharedEdge0Id, int *outSharedEdge1Id);
    bool TestDelauneyCriterion(const TwoIds &trianglePair);
    void PerformEdgeSwap(const TwoIds &trianglePair);
    void UpdateTriangleAdjacency(int triangleToUpdateId, int oldAdjacentTriangleId, int newAdjacentTriangleId);
    void ScheduleTrianglePairCheckIfNeeded(int triangle0Id, int triangle1Id);
    void AddTriangle(const TriangleInfo &info);

    //! For non-negative values the method returns the value modulo <c>3</c>. Efficiency degrades with higher values.
    static int Mod3(int value);

    std::unique_ptr<VertexSet> vertexSet_;
    Core::BoundingBox<float>   boundingBox_;
    std::vector<TriangleInfo>  triangles_;
    int                        outerTriangleVertex0Id_;
    int                        outerTriangleVertex1Id_;
    int                        outerTriangleVertex2Id_;
    bool                       computed_;
    float                      edgeHitEpsilon_;
    int                        cursor_;

    int numEdgeHits_;
    int numInteriorSplits_;
    int numTrianglePairChecks_;
    int numTrianglePairChecksRejected_;
    int numEdgeSwaps_;

    // These are only present during computation...
    std::unique_ptr<std::deque<TwoIds>>                                                 trianglePairsToCheck_;
    std::unique_ptr<std::unordered_set<FourIdsCanonical, FourIdsCanonicalHashFunction>> pointQuadruplesChecked_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_DELAUNEYTRIANGULATIONXY_H_
