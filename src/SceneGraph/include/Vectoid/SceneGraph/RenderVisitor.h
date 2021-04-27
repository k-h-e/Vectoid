#ifndef VECTOID_SCENEGRAPH_RENDERVISITOR_H_
#define VECTOID_SCENEGRAPH_RENDERVISITOR_H_

#include <Vectoid/SceneGraph/VisitorInterface.h>

namespace Vectoid {
namespace SceneGraph {

//! Render visitor.
class RenderVisitor : public virtual VisitorInterface {
  public:
    void Visit(Node *node) override;
    void Leave(Node *node) override;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_RENDERVISITOR_H_

