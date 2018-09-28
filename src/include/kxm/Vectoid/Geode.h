#ifndef KXM_VECTOID_GEODE_H_
#define KXM_VECTOID_GEODE_H_

#include <memory>
#include <kxm/Vectoid/SceneGraphNode.h>
#include <kxm/Vectoid/GeometryInterface.h>

namespace kxm {
namespace Vectoid {

//! This scene graph node represents actual geometry in the scene (geode = geometry node).
/*! 
 *  \ingroup Vectoid
 */ 
class Geode : public SceneGraphNode {
  public:
    Geode(const Geode &other) = delete;
    Geode &operator=(const Geode &other) = delete;
    void Render();
    
  protected:
    Geode(const std::shared_ptr<GeometryInterface> &geometry);
    
  private:
    std::shared_ptr<GeometryInterface> geometry_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_GEODE_H_
