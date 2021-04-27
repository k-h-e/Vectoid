#ifndef VECTOID_SCENEGRAPH_SIMPLELIGHTING_H_
#define VECTOID_SCENEGRAPH_SIMPLELIGHTING_H_

#include <Vectoid/SceneGraph/Node.h>

namespace Vectoid {
namespace SceneGraph {

//! Simple lighting setup using one light source.
class SimpleLighting : public Node {
  public:
    SimpleLighting(const SimpleLighting &other)             = delete;
    SimpleLighting &operator=(const SimpleLighting &other)  = delete;
    SimpleLighting(const SimpleLighting &&other)            = delete;
    SimpleLighting &operator=(const SimpleLighting &&other) = delete;

    void Visit(VisitorInterface *visitor) override;

  protected:
    SimpleLighting();
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_SIMPLELIGHTING_H_
