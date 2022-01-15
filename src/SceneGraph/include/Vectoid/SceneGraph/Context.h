#ifndef VECTOID_SCENEGRAPH_CONTEXT_H_
#define VECTOID_SCENEGRAPH_CONTEXT_H_

#include <K/Core/Interface.h>
#include <K/Core/ReusableItems.h>

namespace Vectoid {
namespace SceneGraph {

class Node;

//! Base class to entities holding context information for scene graph nodes.
/*!
 *  Intended to be subclassed in rendering-platform-specific way.
 */
class Context : public virtual K::Core::Interface {
  public:
    Context();
    Context(const Context &other)            = delete;
    Context &operator=(const Context &other) = delete;
    Context(Context &&other)                 = delete;
    Context &operator=(Context &&other)      = delete;

    //! Registers the specified node with the context.
    /*!
     *  The context will keep a weak reference to the node until it gets unregistered again.
     *
     *  \return
     *  Id for later unregistration.
     */
    int RegisterNode(Node *node);
    //! Unregisters the node identified by the specified id (that was obtained earlier via <c>RegisterNode()</c>).
    void UnregisterNode(int nodeId);

  private:
    K::Core::ReusableItems<Node *> nodes_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_CONTEXT_H_
