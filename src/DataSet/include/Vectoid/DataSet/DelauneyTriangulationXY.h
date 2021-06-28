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

class TriangleTreeXY;

//! Generates a Delauney triangulation for a set of vertices in the <c>x/y</c>-plane.
class DelauneyTriangulationXY : public virtual Core::TriangleProviderInterface {
  public:
    DelauneyTriangulationXY();
    DelauneyTriangulationXY(const DelauneyTriangulationXY &other)             = delete;
    DelauneyTriangulationXY &operator=(const DelauneyTriangulationXY &other)  = delete;
    DelauneyTriangulationXY(const DelauneyTriangulationXY &&other)            = delete;
    DelauneyTriangulationXY &operator=(const DelauneyTriangulationXY &&other) = delete;

    //! Adds the specified point in the <c>x/y</c>-plane (<c>z</c> coordinate will be zeroed).
    /*!
     *  Duplicates are ignored.
     *
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
    //! Can be used after a successful computation to take over the triangulation's resources, in order to continue
    //! working with them.
    /*!
     *  The triangulation will be reset, and a new computation can be begun by adding points via <c>Add()</c>.
     *
     *  \return
     *  <c>false</c> in case there is no result of a successful computation. In this case, the output shared pointers
     *  will be nulled, the other output parameters will be undefined.
     */
    bool Reap(std::shared_ptr<TriangleTreeXY> *outTriangleTree, std::shared_ptr<VertexSet> *outVertexSet,
              ThreeIds *outOuterTriangle);

    virtual void PrepareToProvideTriangles();
    virtual bool ProvideNextTriangle(Core::ThreePoints *outTriangle);
    virtual void ProvideNormal(Core::Vector<float> *outNormal);
    virtual bool TriangleError();

  private:
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

    void Reset();
    void GenerateInitialOuterTriangle();
    void InsertVertex(int pointId);
    void EnforceDelauneyCriterion();
    int TestEdgeHit(int triangleId, const Core::Vector<float> &point);
    void InsertPointEdgeHitCase(int oldTriangleId, int edgeId, int pointId);
    void InsertPointInteriorCase(int oldTriangleId, int pointId);
    bool TestDelauneyCriterion(const TwoIds &trianglePair);
    void PerformEdgeSwap(const TwoIds &trianglePair);
    void ScheduleTrianglePairCheckIfNeeded(int triangle0Id, int triangle1Id);

    std::shared_ptr<VertexSet>      vertexSet_;
    Core::BoundingBox<float>        boundingBox_;
    std::shared_ptr<TriangleTreeXY> triangleTree_;
    int                             outerTriangleVertex0Id_;
    int                             outerTriangleVertex1Id_;
    int                             outerTriangleVertex2Id_;
    bool                            computed_;
    bool                            computationSuccessful_;
    float                           edgeHitEpsilon_;

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
