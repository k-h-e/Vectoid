#ifndef KXM_ZARCH_SAUCERGEOMETRY_H_
#define KXM_ZARCH_SAUCERGEOMETRY_H_

#include <kxm/Zarch/SimpleGeometry.h>

namespace kxm {
namespace Zarch {

//! Initial, simple geometry for the enemy saucers.
/*!
 *  \ingroup Zarch
 */
class SaucerGeometry : public SimpleGeometry {
  public:
    SaucerGeometry();
    
  private:
    SaucerGeometry(const SaucerGeometry &other);
    SaucerGeometry &operator=(const SaucerGeometry &other);
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_SAUCERGEOMETRY_H_
