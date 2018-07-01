#ifndef KXM_VECTOID_DEVICEINTERFACE_H_
#define KXM_VECTOID_DEVICEINTERFACE_H_

#include <memory>
#include <kxm/Core/Interface.h>

namespace kxm {
namespace Vectoid {

class AgeColoredParticles;
class Camera;
class CoordSys;
class Glyphs;
class Particles;
class ParticlesRenderer;
class PerspectiveProjection;
class TestTriangle;
class TextConsole;

//! Interface to <c>Vectoid</c> devices.
/*!
 *  \ingroup Vectoid
 *
 *  A <c>Vectoid</c> device represents a rendering target and acts as rendering-platform-specific factory for scene
 *  graph nodes and associated resources.
 */
class DeviceInterface : public virtual Core::Interface {
  public:
    virtual std::shared_ptr<AgeColoredParticles> newAgeColoredParticles() = 0;
    virtual std::shared_ptr<Camera> newCamera() = 0;
    virtual std::shared_ptr<CoordSys> newCoordSys() = 0;
    virtual std::shared_ptr<Glyphs> newGlyphs() = 0;
    virtual std::shared_ptr<ParticlesRenderer> newParticlesRenderer(std::shared_ptr<Particles> particles) = 0;
    virtual std::shared_ptr<PerspectiveProjection> newPerspectiveProjection() = 0;
    virtual std::shared_ptr<TestTriangle> newTestTriangle() = 0;
    virtual std::shared_ptr<TextConsole> newTextConsole(int width, int height, float glyphWidth, float glyphHeight,
                                                        std::shared_ptr<Glyphs> glyphs) = 0;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_DEVICEINTERFACE_H_

