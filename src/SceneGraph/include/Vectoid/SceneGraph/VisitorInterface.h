#ifndef VECTOID_SCENEGRAPH_VISITORINTERFACE_H_
#define VECTOID_SCENEGRAPH_VISITORINTERFACE_H_

#include <K/Core/Interface.h>

namespace Vectoid {
namespace SceneGraph {

class Node;

//! Interface to scene graph visitors.
class VisitorInterface : public virtual K::Core::Interface {
  public:
    virtual void Visit(Node *node) = 0;
    virtual void Leave(Node *node) = 0;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VISITORINTERFACE_H_

