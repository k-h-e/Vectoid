///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_KDTREE_H_
#define VECTOID_DATASET_KDTREE_H_

#include <unordered_set>
#include <vector>
#include <Vectoid/Core/Transform.h>
#include <Vectoid/DataSet/ItemIntersection.h>

namespace Vectoid {
namespace DataSet {

class Points;

//! kD-tree in 3-space.
/*!
 *  Spatial index structure for point sets, supporting efficient nearest neighbor and sphere intersection queries.
 *
 *  For symmetry with the <c>BoundingBoxTree</c>, the points are represented exclusively by leaf nodes, and the actual
 *  point (coordinate) data is stored externally. If really needed, time (and space) efficiency could be enhanced by
 *  storing the coordinate data inside the tree, with each tree node - including the inner nodes - representing a point.
 *  Quite probably though, this won't be necessary.
 *
 *  Implementation derived from <c>Harvey</c> code base.
 */
class KDTree : public virtual K::Core::Interface {
  public:
    KDTree(const std::shared_ptr<Points> &points);
    KDTree(const KDTree &other)            = delete;
    KDTree &operator=(const KDTree &other) = delete;
    KDTree(KDTree &&other)                 = delete;
    KDTree &operator=(KDTree &&other)      = delete;

    //! Retrieves the set point closest to the query point.
    /*!
     *  \returns
     *  <c>false</c> in case the set is empty. The output parameter is then undefined.
     */
    bool QueryNearestNeighbor(const Core::Vector<float> &queryPoint, int *outNearestNeighbor);
    //! Retrieves all set points inside the specified query sphere.
    void QuerySphereIntersection(const Core::Vector<float> &sphereCenter, float sphereRadius,
                                 std::vector<ItemIntersection> *outIntersections);
    //! Runs an integrity check on the tree and reports whether it has been constructed properly.
    /*!
     *  Method will eventually get removed.
     */
    bool CheckIntegrity();

  private:
    struct Node {
        int   splittingAxisIndex;
        float splittingCoordinate;
        int   leftChild;     // Point ID in case of leaf.
        int   rightChild;    // -1 in case of leaf.

        Node(int aSplittingAxisIndex, float aSplittingCoordinate, int aLeftChild, int aRightChild)
            : splittingAxisIndex(aSplittingAxisIndex),
              splittingCoordinate(aSplittingCoordinate),
              leftChild(aLeftChild),
              rightChild(aRightChild) {}
        Node(const Node &other)            = default;
        Node &operator=(const Node &other) = default;
        Node(Node &&other)                 = default;
        Node &operator=(Node &&other)      = default;
    };

    int AddSubTree(std::vector<int> &indices, int offset, int size, int depth);
    //! Part of nearest neighbor search.
    /*!
     *  Recursively descends into the (box-shaped) space partition containing the query point, takes its data point as
     *  first solution candidate, and then unwinds the call stack, invoking solution enhancement procedures (see
     *  <c>CheckForBetterNearestNeighborCandidate()</c>) for appropriate subtrees at each recursion level.
     */
    int FindNearestNeighbor(const Core::Vector<float> &queryPoint, int node);
    void RefineNearestNeighbor(const Core::Vector<float> &queryPoint, int node, int *inOutCandidate,
                               float *inOutCandidateDistance);
    void PerformSphereQuery(const Core::Vector<float> &sphereCenter, float sphereRadius, int node,
                            std::vector<ItemIntersection> *outIntersections);
    bool IsLeftSubTreeInReach(const Node &nodeInfo, const Core::Vector<float> &queryPoint, float distance);
    bool IsRightSubTreeInReach(const Node &nodeInfo, const Core::Vector<float> &queryPoint, float distance);

    // Integrity checking...
    void CollectPoints(int node, std::unordered_set<int> *points);
    bool CheckNode(int node);

    std::shared_ptr<Points> points_;
    std::vector<Node>       nodes_;
    int                     root_;      // -1 <=> tree empty.
    int                     depth_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_KDTREE_H_
