#ifndef VECTOID_SCENEGRAPH_NODE_H_
#define VECTOID_SCENEGRAPH_NODE_H_

#include <string>
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

    //! Sets the node's name as specified.
    void SetName(const std::string &name);
    //! Returns the node's name. Will be empty if none has been set.
    std::string Name() const;
    //! Enables/disables the node.
    /*!
     *  Disabling a node effectively disables the subtree headed by the node. Re-enabling the node re-enables the
     *  subtree according to the subtree nodes' enabled states.
     */
    void setEnabled(bool enabled);
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
    Node();
    
  private:
    std::string name_;
    bool        enabled_;

};

//! Makes the specified visitor visit the specified sub scene graph.
void Visit(const std::shared_ptr<Node> &node, VisitorInterface *visitor, bool visitAll);

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_NODE_H_
