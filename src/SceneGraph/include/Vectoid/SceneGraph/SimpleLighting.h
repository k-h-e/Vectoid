#ifndef VECTOID_SCENEGRAPH_SIMPLELIGHTING_H_
#define VECTOID_SCENEGRAPH_SIMPLELIGHTING_H_

#include <Vectoid/SceneGraph/SceneGraphNode.h>

namespace Vectoid {
namespace SceneGraph {

//! Simple lighting setup using one light source.
/*!
 *  \ingroup Vectoid
 */
class SimpleLighting : public SceneGraphNode {
  public:
    SimpleLighting(const SimpleLighting &other)             = delete;
    SimpleLighting &operator=(const SimpleLighting &other)  = delete;
    SimpleLighting(const SimpleLighting &&other)            = delete;
    SimpleLighting &operator=(const SimpleLighting &&other) = delete;

  protected:
    SimpleLighting();

    bool settingsChanged_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_SIMPLELIGHTING_H_
