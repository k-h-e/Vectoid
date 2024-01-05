///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/GroupNode.h>

#include <cstdio>
#include <cassert>
#include <Vectoid/SceneGraph/VisitorInterface.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {
    
GroupNode::GroupNode(const shared_ptr<Context> &context)
        : TreeNode(context) {
    // Nop.
}

GroupNode::~GroupNode() {
    // Nop.
}

void GroupNode::AddChild(const shared_ptr<TreeNode> &child) {
    children_.push_back(child);
}

void GroupNode::AddAsLastChild(const shared_ptr<TreeNode> &child) {
    lastChild_ = child;
}

void GroupNode::RemoveChild(const std::shared_ptr<TreeNode> &child) {
    std::vector<shared_ptr<TreeNode>> oldChildren = children_;
    children_.clear();
    for (const shared_ptr<TreeNode> &aChild : oldChildren) {
        if (aChild != child) {
            children_.push_back(aChild);
        }
    }
    if (lastChild_ == child) {
        lastChild_.reset();
    }
}

void GroupNode::RemoveAllChildren() {
    children_.clear();
    lastChild_.reset();
}

void GroupNode::OnVisited(VisitorInterface *visitor, bool visitAll) {
    for (shared_ptr<TreeNode> &child : children_) {
        Visit(child, visitor, visitAll);
    }
    if (lastChild_) {
        Visit(lastChild_, visitor, visitAll);
    }
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
