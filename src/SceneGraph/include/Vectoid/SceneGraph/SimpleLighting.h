#ifndef VECTOID_SCENEGRAPH_SIMPLELIGHTING_H_
#define VECTOID_SCENEGRAPH_SIMPLELIGHTING_H_

#include <Vectoid/SceneGraph/TreeNode.h>

namespace Vectoid {
namespace SceneGraph {

//! Simple lighting setup using one light source.
class SimpleLighting : public TreeNode {
  public:
    SimpleLighting()                                        = delete;
    SimpleLighting(const SimpleLighting &other)             = delete;
    SimpleLighting &operator=(const SimpleLighting &other)  = delete;
    SimpleLighting(const SimpleLighting &&other)            = delete;
    SimpleLighting &operator=(const SimpleLighting &&other) = delete;

  protected:
    SimpleLighting(const std::shared_ptr<Context> &context);
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_SIMPLELIGHTING_H_
