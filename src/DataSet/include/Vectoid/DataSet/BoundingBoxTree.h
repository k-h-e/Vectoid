///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_BOUNDINGBOXTREE_H_
#define VECTOID_DATASET_BOUNDINGBOXTREE_H_

#include <memory>
#include <vector>

#include <K/Core/SafelySerializableInterface.h>
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
    //! Creates a bounding box tree for the specified item collection.
    BoundingBoxTree(const std::shared_ptr<SupportsBoundingBoxTreeInterface> &items);
    //! Restores a bounding box tree for the specified item collection by loading state data previously generated via
    //! Save().
    BoundingBoxTree(const std::shared_ptr<SupportsBoundingBoxTreeInterface> &items,
                    K::Core::BlockingInStreamInterface &stream);
    BoundingBoxTree()                                       = delete;
    BoundingBoxTree(const BoundingBoxTree &other)            = delete;
    BoundingBoxTree &operator=(const BoundingBoxTree &other) = delete;
    BoundingBoxTree(BoundingBoxTree &&other)                 = delete;
    BoundingBoxTree &operator=(BoundingBoxTree &&other)      = delete;
    ~BoundingBoxTree()                                       = default;
    
    //! Tells whether the tree is empty.
    bool Empty() const;
    //! Computes the intersection with the specified line.
    /*!
     *  \return <c>false</c> in case of failure. The output parameter will then be undefined.
     */
    bool ComputeLineIntersection(const Core::Vector<float> &linePoint, const Core::Vector<float> &lineDirection,
                                 std::vector<ItemIntersection> &outIntersections);
    //! Creates an independent copy of the boundig box tree.
    /*!
     *  \param clonedItems
     *  An independent copy of the underlying items must be passed in by the caller.
     */
    std::unique_ptr<BoundingBoxTree> Clone(const std::shared_ptr<SupportsBoundingBoxTreeInterface> &clonedItems);
    //! Retrieves the bounding box for the tree's entire item colection.
    /*!
     *  \return <c>false</c> in case the tree is empty. The output bounding box will then be in "undefined" state.
     */
    bool GetBoundingBox(Vectoid::Core::BoundingBox<float> &outBox) const;
    //! Saves the tree state to the specified stream (excluding the content of the underlying item collection).
    void Save(K::Core::BlockingOutStreamInterface &stream) const;

  private:
    struct Node : public virtual K::Core::SafelySerializableInterface {
        Core::BoundingBox<float> boundingBox;
        int                      leftChild;     // Item ID in case of leaf.
        int                      rightChild;    // -1 in case of leaf.
        
        Node(const Core::BoundingBox<float> &aBoundingBox, int aLeftChild, int aRightChild);
        Node();
        
        // SafelySerializableInterface...
        void Serialize(K::Core::BlockingOutStreamInterface &stream) const override;
        void Deserialize(K::Core::BlockingInStreamInterface &stream) override;
        bool DeserializeAndValidate(K::Core::BlockingInStreamInterface &stream) override;
    };
    struct Comparer {
        std::shared_ptr<SupportsBoundingBoxTreeInterface> items;
        Core::Axis                                        comparisonAxis;
        Comparer(const std::shared_ptr<SupportsBoundingBoxTreeInterface> &someItems);
        void SetComparisonAxis(Core::Axis axis);
        bool operator()(int left, int right);
    };

    BoundingBoxTree(const BoundingBoxTree &other, const std::shared_ptr<SupportsBoundingBoxTreeInterface> &items);
    
    int AddSubTree(std::vector<int> &itemIds, int offset, int numItems, int depth);
    bool ComputeSubTreeLineIntersection(
        int node, const Core::Vector<float> &linePoint, const Core::Vector<float> &lineDirection,
        std::vector<int> &outItemsToTest);
    void Load(K::Core::BlockingInStreamInterface &stream);

    std::shared_ptr<SupportsBoundingBoxTreeInterface> items_;
    std::vector<Node>                                 nodes_;       // Empty <=> tree empty.
    int                                               root_;        // -1    <=> tree empty.
    Comparer                                          comparer_;
    int                                               depth_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_BOUNDINGBOXTREE_H_

