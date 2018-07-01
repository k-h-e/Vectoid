#ifndef KXM_VECTOID_OPENGL_DEVICE_H_
#define KXM_VECTOID_OPENGL_DEVICE_H_

#include <kxm/Vectoid/DeviceInterface.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

//! <c>Vectoid</c> device for rendering via <c>OpenGL</c>.
/*!
 *  \ingroup VectoidOpenGL
 */
class Device : public virtual Vectoid::DeviceInterface {
  public:
    virtual std::shared_ptr<AgeColoredParticles> newAgeColoredParticles();
    virtual std::shared_ptr<Camera> newCamera();
    virtual std::shared_ptr<CoordSys> newCoordSys();
    virtual std::shared_ptr<Glyphs> newGlyphs();
    virtual std::shared_ptr<ParticlesRenderer> newParticlesRenderer(std::shared_ptr<Particles> particles);
    virtual std::shared_ptr<PerspectiveProjection> newPerspectiveProjection();
    virtual std::shared_ptr<TestTriangle> newTestTriangle();
    virtual std::shared_ptr<TextConsole> newTextConsole(int width, int height, float glyphWidth, float glyphHeight,
                                                        std::shared_ptr<Glyphs> glyphs);
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_OPENGL_DEVICE_H_
