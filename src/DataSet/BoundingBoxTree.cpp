///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/BoundingBoxTree.h>

#include <algorithm>
#include <cassert>
#include <vector>
#include <K/Core/Log.h>
#include <Vectoid/Core/BoundingBox.h>
#include <Vectoid/Math/Intersection/LineBoundingBoxIntersection.h>
#include <Vectoid/DataSet/SupportsBoundingBoxTreeInterface.h>

using std::shared_ptr;
using std::sort;
using std::to_string;
using std::unique_ptr;
using std::vector;
using K::Core::Log;
using Vectoid::Core::Axis;
using Vectoid::Core::BoundingBox;
using Vectoid::Core::Vector;
using Vectoid::Math::Intersection::LineBoundingBoxIntersection;
using Vectoid::DataSet::SupportsBoundingBoxTreeInterface;

namespace Vectoid {
namespace DataSet {

BoundingBoxTree::BoundingBoxTree(const shared_ptr<SupportsBoundingBoxTreeInterface> &items)
        : items_(items),
          root_(-1),
          comparer_(items),
          depth_(0) {
    if (items_->Size() > 0) {
        vector<int> itemIds;
        for (int i = 0; i < items_->Size(); ++i) {
            itemIds.push_back(i);
        }
        root_ = AddSubTree(&itemIds, 0, items_->Size(), 1);
        Log::Print(Log::Level::Debug, this, [&]{ return "bounding box tree generated, depth=" + to_string(depth_); });
    } else {
        Log::Print(Log::Level::Warning, this, []{ return "bounding box tree undefined"; });
    }
}

// Private helper constructor to Clone().
BoundingBoxTree::BoundingBoxTree(const BoundingBoxTree &other,
                                 const shared_ptr<SupportsBoundingBoxTreeInterface> &items)
        : items_(items),
          nodes_(other.nodes_),
          root_(other.root_),
          comparer_(items),
          depth_(other.depth_) {
    // Nop.
}

bool BoundingBoxTree::ComputeLineIntersection(const Vector<float> &linePoint, const Vector<float> &lineDirection,
                                              vector<ItemIntersection> *outIntersections) {
    outIntersections->clear();
    if (root_ == -1) {
        return true;    // We're empty.
    } else {
        vector<int> itemsToTest;
        if (!ComputeSubTreeLineIntersection(root_, linePoint, lineDirection, &itemsToTest)) {
            return false;
        }

        for (int item : itemsToTest) {
            bool             intersects;
            ItemIntersection intersection;
            if (!items_->ComputeLineItemIntersection(linePoint, lineDirection, item, &intersects, &intersection)) {
                return false;
            }
            if (intersects) {
                outIntersections->push_back(intersection);
            }
        }

        return true;
    }
}

unique_ptr<BoundingBoxTree> BoundingBoxTree::Clone(const shared_ptr<SupportsBoundingBoxTreeInterface> &clonedItems) {
    return unique_ptr<BoundingBoxTree>(new BoundingBoxTree(*this, clonedItems));
}

int BoundingBoxTree::AddSubTree(std::vector<int> *itemIds, int offset, int numItems, int depth) {
    assert (numItems > 0);

    if (depth > depth_) {
        depth_ = depth;
    }

    BoundingBox<float> boundingBox;
    for (int i = 0; i < numItems; ++i) {
        BoundingBox<float> itemBoundingBox;
        items_->GetItemBoundingBox((*itemIds)[offset + i], &itemBoundingBox);
        boundingBox.Grow(itemBoundingBox);
    }

    if (numItems == 1) {    // Leaf case.
        int node = static_cast<int>(nodes_.size());
        nodes_.push_back(Node(boundingBox, (*itemIds)[offset], -1));
        return node;
    } else {    // numItems > 1.
        comparer_.SetComparisonAxis(boundingBox.LargestExtentAxis());
        sort(itemIds->begin() + offset, itemIds->begin() + offset + numItems, comparer_);
        int numLeft = numItems / 2;    // >= 1.
        int leftChild  = AddSubTree(itemIds, offset, numLeft, depth + 1);
        int rightChild = AddSubTree(itemIds, offset + numLeft, numItems - numLeft, depth + 1);
        int node = static_cast<int>(nodes_.size());
        nodes_.push_back(Node(boundingBox, leftChild, rightChild));
        return node;
    }
}

bool BoundingBoxTree::ComputeSubTreeLineIntersection(
        int node, const Vector<float> &linePoint, const Vector<float> &lineDirection, vector<int> *outItemsToTest) {
    Node &nodeInfo = nodes_[node];
    bool intersects;
    if (LineBoundingBoxIntersection::Compute(linePoint, lineDirection, nodeInfo.boundingBox, &intersects)) {
        if (intersects) {
            if (nodeInfo.rightChild == -1) {    // Leaf case.
                outItemsToTest->push_back(nodeInfo.leftChild);
                return true;
            } else {
                if (ComputeSubTreeLineIntersection(nodeInfo.leftChild, linePoint, lineDirection, outItemsToTest)
                        && ComputeSubTreeLineIntersection(nodeInfo.rightChild, linePoint, lineDirection,
                                                          outItemsToTest)) {
                    return true;
                }
            }
        } else {
            return true;
        }
    }

    return false;
}

BoundingBoxTree::Comparer::Comparer(const shared_ptr<SupportsBoundingBoxTreeInterface> &someItems)
        : items(someItems),
          comparisonAxis(Axis::X) {
    // Nop.
}

void BoundingBoxTree::Comparer::SetComparisonAxis(Axis axis) {
    comparisonAxis = axis;
}

bool BoundingBoxTree::Comparer::operator()(int left, int right) {
    BoundingBox<float> boundingBox;
    items->GetItemBoundingBox(left, &boundingBox);
    auto leftCenter = boundingBox.Center();
    items->GetItemBoundingBox(right, &boundingBox);
    auto rightCenter = boundingBox.Center();

    switch (comparisonAxis) {
        case Axis::Y:
            return (leftCenter.y < rightCenter.y);
        case Axis::Z:
            return (leftCenter.z < rightCenter.z);
        case Axis::X:
        default:
            return (leftCenter.x < rightCenter.x);
    }
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
