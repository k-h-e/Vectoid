#ifndef VECTOID_SCENEGRAPH_NODE_H_
#define VECTOID_SCENEGRAPH_NODE_H_

#include <memory>
#include <string>
#include <K/Core/Interface.h>

namespace Vectoid {
//! Scene graph for 3D graphics.
namespace SceneGraph {

class Context;

//! Base class to all scene graph nodes.
class Node : public virtual K::Core::Interface {
  public:
    Node()                             = delete;
    Node(const Node &other)            = delete;
    Node &operator=(const Node &other) = delete;
    Node(Node &&other)                 = delete;
    Node &operator=(Node &&other)      = delete;
    ~Node();

    //! Sets the node's name as specified.
    void SetName(const std::string &name);
    //! Returns the node's name. Will be empty if none has been set.
    std::string Name() const;

  protected:
    Node(const std::shared_ptr<Context> &context);

    std::shared_ptr<Context> context_;

  private:
    std::string name_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_NODE_H_
