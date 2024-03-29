///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_GROUPNODE_H_
#define VECTOID_SCENEGRAPH_GROUPNODE_H_

#include <vector>
#include <memory>
#include <Vectoid/SceneGraph/TreeNode.h>

namespace Vectoid {
namespace SceneGraph {

//! Base class to all scene graph group nodes.
class GroupNode : public TreeNode {
  public:
    GroupNode()                                  = delete;
    GroupNode(const GroupNode &other)            = delete;
    GroupNode &operator=(const GroupNode &other) = delete;
    GroupNode(GroupNode &&other)                 = delete;
    GroupNode &operator=(GroupNode &&other)      = delete;
    ~GroupNode();
    //! Adds the specified node as child of the receiver node.
    void AddChild(const std::shared_ptr<TreeNode> &child);
    //! Adds the specified node as child in a special slot: if the "last" child is present, it will always be visited
    //! last, e.g. when rendering.
    /*!
     *  If a child node was already attached in the "last child" slot, it is removed. 
     */
    void AddAsLastChild(const std::shared_ptr<TreeNode> &child);
    //! Removes the specified child from the node, if it is in fact registered as a child.
    void RemoveChild(const std::shared_ptr<TreeNode> &child);
    //! Removes all child nodes from the scene graph node.
    void RemoveAllChildren();

    void OnVisited(VisitorInterface *visitor, bool visitAll) override final;
    
  protected:
    GroupNode(const std::shared_ptr<Context> &context);
    
  private:
    std::vector<std::shared_ptr<TreeNode>> children_;
    std::shared_ptr<TreeNode>              lastChild_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_GROUPNODE_H_
