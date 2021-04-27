#ifndef VECTOID_SCENEGRAPH_NODE_H_
#define VECTOID_SCENEGRAPH_NODE_H_

#include <K/Core/Interface.h>

namespace Vectoid {
//! Scene graph for 3D graphics.
namespace SceneGraph {

class VisitorInterface;

//! Base class to all scene graph nodes.
class Node : public virtual K::Core::Interface {
  public:
    Node(const Node &other)            = delete;
    Node &operator=(const Node &other) = delete;
    Node(Node &&other)                 = delete;
    Node &operator=(Node &&other)      = delete;
    ~Node();

    //! Makes the specified visitor visit the sub scene graph rooted in the node.
    virtual void Visit(VisitorInterface *visitor);
    //! Renders the node.
    /*!
     *  Called by the RenderVisitor when it first visits the node, before descending into the node's children.
     *
     *  This method and RenderPost() are the only scene graph node operations that are allowed to interact with the
     *  underlying graphics platform.
     */
    virtual void RenderPre();
    //! Finiashes rendering the node.
    /*!
     *  Called by the RenderVisitor when it leaves the node, after ascending again from the node's children.
     *
     *  This method and RenderPre() are the only scene graph node operations that are allowed to interact with the
     *  underlying graphics platform.
     */
    virtual void RenderPost();
    
  protected:
    Node();
    
  private:

};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_NODE_H_
