///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/TreeNode.h>

#include <Vectoid/SceneGraph/VisitorInterface.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {
    
TreeNode::TreeNode(const shared_ptr<Context> &context)
        : Node(context),
          enabled_(true) {
    // Nop.
}

TreeNode::~TreeNode() {
    // Nop.
}

void TreeNode::SetEnabled(bool enabled) {
    enabled_ = enabled;
}

bool TreeNode::Enabled() const {
    return enabled_;
}

void TreeNode::RenderPre() {
    // Nop.
}

void TreeNode::RenderPost() {
    // Nop.
}

void TreeNode::OnVisited(VisitorInterface *visitor, bool visitAll) {
    (void)visitor;
    (void)visitAll;
    // Nop.
}

void Visit(const shared_ptr<TreeNode> &node, VisitorInterface *visitor, bool visitAll) {
    if (visitAll || node->Enabled()) {
        visitor->Visit(node);
        node->OnVisited(visitor, visitAll);
        visitor->Leave(node);
    }
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
