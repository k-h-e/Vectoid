///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/BoundingBoxTree.h>

#include <algorithm>
#include <cassert>
#include <vector>

#include <K/Core/BlockingOutStreamInterface.h>
#include <K/Core/Log.h>
#include <Vectoid/Core/BoundingBox.h>
#include <Vectoid/Math/Intersection/LineBoundingBoxIntersection.h>
#include <Vectoid/DataSet/SupportsBoundingBoxTreeInterface.h>

using std::shared_ptr;
using std::sort;
using std::to_string;
using std::unique_ptr;
using std::vector;

using K::Core::BlockingInStreamInterface;
using K::Core::BlockingOutStreamInterface;
using K::Core::Log;
using Vectoid::Core::Axis;
using Vectoid::Core::BoundingBox;
using Vectoid::Core::Vector;
using Vectoid::Math::Intersection::LineBoundingBoxIntersection;
using Vectoid::DataSet::SupportsBoundingBoxTreeInterface;

namespace Vectoid {
namespace DataSet {

BoundingBoxTree::BoundingBoxTree(const shared_ptr<SupportsBoundingBoxTreeInterface> &items)
        : items_{items},
          root_{-1},
          comparer_{items},
          depth_{0} {
    if (items_->Size() > 0) {
        Log::Print(Log::Level::Debug, this, [&]{
            return "generating bounding box tree, num_items=" + to_string(items_->Size()) + " ...";
        });
        vector<int> itemIds;
        for (int i = 0; i < items_->Size(); ++i) {
            itemIds.push_back(i);
        }
        root_ = AddSubTree(itemIds, 0, items_->Size(), 1);
        Log::Print(Log::Level::Debug, this, [&]{
            return "    bounding box tree generated, num_nodes=" + to_string(nodes_.size()) + ", depth="
                + to_string(depth_);
        });
    } else {
        Log::Print(Log::Level::Warning, this, []{ return "bounding box tree empty"; });
    }
}

BoundingBoxTree::BoundingBoxTree(const shared_ptr<SupportsBoundingBoxTreeInterface> &items,
                                 BlockingInStreamInterface &stream)
        : items_{items},
          root_{-1},
          comparer_{items},
          depth_{0} {
    Load(stream);
}

// Private helper constructor to Clone().
BoundingBoxTree::BoundingBoxTree(const BoundingBoxTree &other,
                                 const shared_ptr<SupportsBoundingBoxTreeInterface> &items)
        : items_{items},
          nodes_{other.nodes_},
          root_{other.root_},
          comparer_{items},
          depth_{other.depth_} {
    // Nop.
}

bool BoundingBoxTree::Empty() const {
    return (root_ == -1);
}

bool BoundingBoxTree::ComputeLineIntersection(const Vector<float> &linePoint, const Vector<float> &lineDirection,
                                              vector<ItemIntersection> &outIntersections) {
    outIntersections.clear();
    if (root_ == -1) {
        return true;    // We're empty.
    } else {
        vector<int> itemsToTest;
        if (!ComputeSubTreeLineIntersection(root_, linePoint, lineDirection, itemsToTest)) {
            return false;
        }

        for (int item : itemsToTest) {
            bool             intersects;
            ItemIntersection intersection;
            if (!items_->ComputeLineItemIntersection(linePoint, lineDirection, item, intersects, intersection)) {
                return false;
            }
            if (intersects) {
                outIntersections.push_back(intersection);
            }
        }

        return true;
    }
}

unique_ptr<BoundingBoxTree> BoundingBoxTree::Clone(const shared_ptr<SupportsBoundingBoxTreeInterface> &clonedItems) {
    return unique_ptr<BoundingBoxTree>(new BoundingBoxTree(*this, clonedItems));
}

bool BoundingBoxTree::GetBoundingBox(BoundingBox<float> &outBox) const {
    if (root_ != -1) {
        outBox = nodes_[root_].boundingBox;
        return true;
    } else {
        outBox = BoundingBox<float>();
        return false;
    }
}

void BoundingBoxTree::Save(BlockingOutStreamInterface &stream) const {
    int numNodes { static_cast<int>(nodes_.size()) };
    stream << numNodes;
    for (const Node &node : nodes_) {
        node.Serialize(stream);
    }
    
    stream << root_;
    stream << depth_;
}

// ---

int BoundingBoxTree::AddSubTree(vector<int> &itemIds, int offset, int numItems, int depth) {
    assert (numItems > 0);

    if (depth > depth_) {
        depth_ = depth;
    }

    BoundingBox<float> boundingBox;
    for (int i = 0; i < numItems; ++i) {
        BoundingBox<float> itemBoundingBox;
        items_->GetItemBoundingBox(itemIds[offset + i], itemBoundingBox);
        boundingBox.Grow(itemBoundingBox);
    }

    if (numItems == 1) {    // Leaf case.
        int node = static_cast<int>(nodes_.size());
        nodes_.push_back(Node{boundingBox, itemIds[offset], -1});
        return node;
    } else {    // numItems > 1.
        comparer_.SetComparisonAxis(boundingBox.LargestExtentAxis());
        sort(itemIds.begin() + offset, itemIds.begin() + offset + numItems, comparer_);
        int numLeft    { numItems / 2 };    // >= 1.
        int leftChild  { AddSubTree(itemIds, offset, numLeft, depth + 1) };
        int rightChild { AddSubTree(itemIds, offset + numLeft, numItems - numLeft, depth + 1) };
        int node { static_cast<int>(nodes_.size()) };
        nodes_.push_back(Node{boundingBox, leftChild, rightChild});
        return node;
    }
}

bool BoundingBoxTree::ComputeSubTreeLineIntersection(
        int node, const Vector<float> &linePoint, const Vector<float> &lineDirection, vector<int> &outItemsToTest) {
    Node &nodeInfo { nodes_[node] };
    bool intersects;
    if (LineBoundingBoxIntersection::Compute(linePoint, lineDirection, nodeInfo.boundingBox, intersects)) {
        if (intersects) {
            if (nodeInfo.rightChild == -1) {    // Leaf case.
                outItemsToTest.push_back(nodeInfo.leftChild);
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

void BoundingBoxTree::Load(BlockingInStreamInterface &stream) {
    bool valid { true };
    
    int numNodes;
    stream >> numNodes;
    if (stream.StreamError()) {
        valid = false;
    } else {
        nodes_.clear();
        for (int i = 0; (i < numNodes) && valid; ++i) {
            Node node;
            if (!node.DeserializeAndValidate(stream)) {
                valid = false;
            } else {
                nodes_.push_back(node);
            }
        }
        if (valid) {
            stream >> root_;
            stream >> depth_;
            if (stream.StreamError()) {
                valid = false;
            } else {
                if (root_ == -1) {
                    if ((numNodes != 0) || (depth_ != 0)) {
                        valid = false;
                    }
                } else {
                    if (numNodes < 1) {
                        valid = false;
                    }
                    for (int i = 0; (i < numNodes) && valid; ++i) {
                        Node &node { nodes_[i] };
                        if (node.rightChild == -1) {    // Leaf...
                            if (node.leftChild >= items_->Size()) {
                                valid = false;
                            }
                        } else {                        // Inner node...
                            if ((node.leftChild >= numNodes) || (node.rightChild >= numNodes)) {
                                valid = false;
                            }
                        }
                    }
                    if ((root_ < 0) || (root_ >= numNodes)) {
                        valid = false;
                    }
                    if (depth_ < 1) {
                        valid = false;
                    }
                }
            }
        }
    }
    
    if (valid) {
        Log::Print(Log::Level::Debug, this, [&]{
            return "bounding box tree loaded, num_nodes=" + to_string(nodes_.size()) + ", depth="
                + to_string(depth_); });
    } else {
        nodes_.clear();
        root_  = -1;
        depth_ = 0;
        Log::Print(Log::Level::Warning, this, [&]{ return "failed to load bounding box tree!"; });
    }
}

// ---

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
    items->GetItemBoundingBox(left, boundingBox);
    auto leftCenter = boundingBox.Center();
    items->GetItemBoundingBox(right, boundingBox);
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

// ---

BoundingBoxTree::Node::Node(const BoundingBox<float> &aBoundingBox, int aLeftChild, int aRightChild)
        : boundingBox(aBoundingBox),
          leftChild(aLeftChild),
          rightChild(aRightChild) {
    // Nop.
}

BoundingBoxTree::Node::Node()
        : leftChild(0),
          rightChild(-1) {
    // Nop.
}

void BoundingBoxTree::Node::Serialize(BlockingOutStreamInterface &stream) const {
    boundingBox.Serialize(stream);
    stream << leftChild;
    stream << rightChild;
}

void BoundingBoxTree::Node::Deserialize(BlockingInStreamInterface &stream) {
    boundingBox.Deserialize(stream);
    stream >> leftChild;
    stream >> rightChild;
}

bool BoundingBoxTree::Node::DeserializeAndValidate(BlockingInStreamInterface &stream) {
    bool valid { true };
    
    if (!boundingBox.DeserializeAndValidate(stream)) {
        valid = false;
    } else {
        stream >> leftChild;
        stream >> rightChild;
        if (stream.ErrorState()) {
            valid = false;
        } else {
            if (rightChild == -1) {
                if (leftChild < 0) {
                    valid = false;
                }
            } else {
                if ((leftChild < 0) || (rightChild < 0)) {
                    valid = false;
                }
            }
        }
    }
    
    if (!valid) {
        *this = Node{};
    }
    return valid;
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
