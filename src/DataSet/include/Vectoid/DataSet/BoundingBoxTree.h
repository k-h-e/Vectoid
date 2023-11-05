///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_BOUNDINGBOXTREE_H_
#define VECTOID_DATASET_BOUNDINGBOXTREE_H_

#include <memory>
#include <vector>
#include <K/Core/Interface.h>
#include <Vectoid/Core/BoundingBox.h>
#include <Vectoid/Core/Transform.h>
#include <Vectoid/DataSet/ItemIntersection.h>

namespace Vectoid {
namespace DataSet {

class SupportsBoundingBoxTreeInterface;

//! Axis-aligned bounding box tree.
/*!
 *  Implementation derived from <c>Harvey</c> code base.
 */
class BoundingBoxTree : public virtual K::Core::Interface {
  public:
    //! The item collection must not be empty.
    BoundingBoxTree(const std::shared_ptr<SupportsBoundingBoxTreeInterface> &items);
    BoundingBoxTree(const BoundingBoxTree &other)            = delete;
    BoundingBoxTree &operator=(const BoundingBoxTree &other) = delete;
    BoundingBoxTree(BoundingBoxTree &&other)                 = delete;
    BoundingBoxTree &operator=(BoundingBoxTree &&other)      = delete;

    //! Computes the intersection with the specified line.
    /*!
     *  \return <c>false</c> in case of failure. The output parameter will then be undefined.
     */
    bool ComputeLineIntersection(const Core::Vector<float> &linePoint, const Core::Vector<float> &lineDirection,
                                 std::vector<ItemIntersection> *outIntersections);
    //! Creates an independent copy of the boundig box tree.
    /*!
     *  \param clonedItems
     *  An independent copy of the underlying items must be passed in by the caller.
     */
    std::unique_ptr<BoundingBoxTree> Clone(const std::shared_ptr<SupportsBoundingBoxTreeInterface> &clonedItems);

  private:
    struct Node {
        Core::BoundingBox<float> boundingBox;
        int                      leftChild;     // Item ID in case of leaf.
        int                      rightChild;    // -1 in case of leaf.
        Node(const Core::BoundingBox<float> &aBoundingBox, int aLeftChild, int aRightChild)
            : boundingBox(aBoundingBox), leftChild(aLeftChild), rightChild(aRightChild) {}
    };
    struct Comparer {
        std::shared_ptr<SupportsBoundingBoxTreeInterface> items;
        Core::Axis                                        comparisonAxis;
        Comparer(const std::shared_ptr<SupportsBoundingBoxTreeInterface> &someItems);
        void SetComparisonAxis(Core::Axis axis);
        bool operator()(int left, int right);
    };

    BoundingBoxTree(const BoundingBoxTree &other, const std::shared_ptr<SupportsBoundingBoxTreeInterface> &items);
    int AddSubTree(std::vector<int> *itemIds, int offset, int numItems, int depth);
    bool ComputeSubTreeLineIntersection(
        int node, const Core::Vector<float> &linePoint, const Core::Vector<float> &lineDirection,
        std::vector<int> *outItemsToTest);

    std::shared_ptr<SupportsBoundingBoxTreeInterface> items_;
    std::vector<Node>                                 nodes_;       // Empty <=> tree empty.
    int                                               root_;        // -1    <=> tree empty.
    Comparer                                          comparer_;
    int                                               depth_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_BOUNDINGBOXTREE_H_

