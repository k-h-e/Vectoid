#ifndef KXM_VECTOID_SCENEGRAPHNODE_H_
#define KXM_VECTOID_SCENEGRAPHNODE_H_

#include <vector>
#include <memory>

#include <kxm/Core/Interface.h>

namespace kxm {
namespace Vectoid {
    
class RenderContext;

//! Base class to all scene graph nodes.
/*! 
 *  \ingroup Vectoid
 */ 
class SceneGraphNode : public virtual Core::Interface {
  public:
    SceneGraphNode();
    SceneGraphNode(const SceneGraphNode &other)            = delete;
    SceneGraphNode &operator=(const SceneGraphNode &other) = delete;
    SceneGraphNode(SceneGraphNode &&other)                 = delete;
    SceneGraphNode &operator=(SceneGraphNode &&other)      = delete;
    ~SceneGraphNode();
    //! Adds the specified node as child of the receiver node.
    void AddChild(const std::shared_ptr<SceneGraphNode> &child);
    //! Adds the specified node as child in a special slot: if the "last" child is present, it will always be visited
    //! last, e.g. when rendering.
    /*!
     *  If a child node was already attached in the "last child" slot, it is removed. 
     */
    void AddAsLastChild(const std::shared_ptr<SceneGraphNode> &child);
    //! Removes the specified child from the node, if it is in fact registered as a child.
    void RemoveChild(const std::shared_ptr<SceneGraphNode> &child);
    //! Removes all child nodes from the scene graph node.
    void RemoveAllChildren();
    //! Performs a render traversal of the sub scene graph rooted in the node. This is the only scene graph node
    //! operation that is allowed to interact with <c>OpenGL</c>.
    virtual void Render(RenderContext *context);
    
  private:
    std::vector<std::shared_ptr<SceneGraphNode>> children_;
    std::shared_ptr<SceneGraphNode>              lastChild_;
};
    
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_SCENEGRAPHNODE_H_
