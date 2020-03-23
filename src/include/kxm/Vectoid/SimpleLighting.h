#ifndef KXM_VECTOID_SIMPLELIGHTING_H_
#define KXM_VECTOID_SIMPLELIGHTING_H_

#include <kxm/Vectoid/SceneGraphNode.h>

namespace kxm {
namespace Vectoid {

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

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_SIMPLELIGHTING_H_
