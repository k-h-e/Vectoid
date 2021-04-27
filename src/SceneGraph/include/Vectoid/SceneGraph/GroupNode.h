#ifndef VECTOID_SCENEGRAPH_GROUPNODE_H_
#define VECTOID_SCENEGRAPH_GROUPNODE_H_

#include <vector>
#include <memory>
#include <Vectoid/SceneGraph/Node.h>

namespace Vectoid {
namespace SceneGraph {

//! Base class to all scene graph group nodes.
class GroupNode : public Node {
  public:
    GroupNode(const GroupNode &other)            = delete;
    GroupNode &operator=(const GroupNode &other) = delete;
    GroupNode(GroupNode &&other)                 = delete;
    GroupNode &operator=(GroupNode &&other)      = delete;
    ~GroupNode();
    //! Adds the specified node as child of the receiver node.
    void AddChild(const std::shared_ptr<Node> &child);
    //! Adds the specified node as child in a special slot: if the "last" child is present, it will always be visited
    //! last, e.g. when rendering.
    /*!
     *  If a child node was already attached in the "last child" slot, it is removed. 
     */
    void AddAsLastChild(const std::shared_ptr<Node> &child);
    //! Removes the specified child from the node, if it is in fact registered as a child.
    void RemoveChild(const std::shared_ptr<Node> &child);
    //! Removes all child nodes from the scene graph node.
    void RemoveAllChildren();

    void Visit(VisitorInterface *visitor) override final;
    
  protected:
    GroupNode();
    
  private:
    std::vector<std::shared_ptr<Node>> children_;
    std::shared_ptr<Node>              lastChild_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_GROUPNODE_H_
