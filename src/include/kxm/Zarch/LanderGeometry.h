#ifndef KXM_ZARCH_LANDERGEOMETRY_H_
#define KXM_ZARCH_LANDERGEOMETRY_H_

#include <kxm/Zarch/SimpleGeometry.h>

namespace kxm {
namespace Zarch {

//! Initial, simple geometry for the lander (the vehicle controlled by the player).
/*!
 *  \ingroup Zarch
 */
class LanderGeometry : public SimpleGeometry {
  public:
    LanderGeometry();
    
  private:
    LanderGeometry(const LanderGeometry &other);
    LanderGeometry &operator=(const LanderGeometry &other);
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_LANDERGEOMETRY_H_
