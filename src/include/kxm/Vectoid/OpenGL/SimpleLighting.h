#ifndef KXM_VECTOID_OPENGL_SIMPLELIGHTING_H_
#define KXM_VECTOID_OPENGL_SIMPLELIGHTING_H_

#include <kxm/Vectoid/SimpleLighting.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

//! Simple lighting setup using one light source.
/*!
 *  \ingroup Vectoid
 */
class SimpleLighting : public Vectoid::SimpleLighting {
  public:
    SimpleLighting();
    SimpleLighting(const SimpleLighting &other)             = delete;
    SimpleLighting &operator=(const SimpleLighting &other)  = delete;
    SimpleLighting(const SimpleLighting &&other)            = delete;
    SimpleLighting &operator=(const SimpleLighting &&other) = delete;
    virtual void Render();
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_OPENGL_SIMPLELIGHTING_H_
