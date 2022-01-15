#ifndef VECTOID_SCENEGRAPH_RENDERVISITOR_H_
#define VECTOID_SCENEGRAPH_RENDERVISITOR_H_

#include <Vectoid/SceneGraph/VisitorInterface.h>

namespace Vectoid {
namespace SceneGraph {

//! Render visitor.
class RenderVisitor : public virtual VisitorInterface {
  public:
    void Visit(const std::shared_ptr<TreeNode> &node) override;
    void Leave(const std::shared_ptr<TreeNode> &node) override;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_RENDERVISITOR_H_

