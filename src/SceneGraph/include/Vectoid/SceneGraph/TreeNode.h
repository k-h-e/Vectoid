///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_TREENODE_H_
#define VECTOID_SCENEGRAPH_TREENODE_H_

#include <Vectoid/SceneGraph/Node.h>

namespace Vectoid {
namespace SceneGraph {

class VisitorInterface;

//! Base class to all scene graph tree nodes.
class TreeNode : public Node {
  public:
    TreeNode()                                 = delete;
    TreeNode(const TreeNode &other)            = delete;
    TreeNode &operator=(const TreeNode &other) = delete;
    TreeNode(TreeNode &&other)                 = delete;
    TreeNode &operator=(TreeNode &&other)      = delete;
    ~TreeNode();

    //! Enables/disables the node.
    /*!
     *  Disabling a node effectively disables the subtree headed by the node. Re-enabling the node re-enables the
     *  subtree according to the subtree nodes' enabled states.
     */
    void SetEnabled(bool enabled);
    //! Tells whether the node is enabled.
    bool Enabled() const;
    //! Renders the node.
    /*!
     *  Called by the RenderVisitor when it first visits the node, before descending into the node's children.
     *
     *  This method and RenderPost() are the only scene graph node operations that are allowed to interact with the
     *  underlying graphics platform.
     */
    virtual void RenderPre();
    //! Finishes rendering the node.
    /*!
     *  Called by the RenderVisitor when it leaves the node, after ascending again from the node's children.
     *
     *  This method and RenderPre() are the only scene graph node operations that are allowed to interact with the
     *  underlying graphics platform.
     */
    virtual void RenderPost();
    //! Called between pre and post visiting actions for the node.
    virtual void OnVisited(VisitorInterface *visitor, bool visitAll);

  protected:
    TreeNode(const std::shared_ptr<Context> &context);
    
  private:
    bool enabled_;
};

//! Makes the specified visitor visit the specified sub scene graph.
void Visit(const std::shared_ptr<TreeNode> &node, VisitorInterface *visitor, bool visitAll);

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_TREENODE_H_
