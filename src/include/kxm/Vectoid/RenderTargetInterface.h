#ifndef KXM_VECTOID_RENDERTARGETINTERFACE_H_
#define KXM_VECTOID_RENDERTARGETINTERFACE_H_

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

//! Interface to <c>Vectoid</c> render targets.
/*!
 *  \ingroup Vectoid
 *
 *  A <c>Vectoid</c> render target acts as rendering-platform-specific factory for scene graph nodes and associated
 *  resources.
 */
class RenderTargetInterface : public virtual Core::Interface {
  public:
    virtual std::shared_ptr<AgeColoredParticles> NewAgeColoredParticles(std::shared_ptr<Particles> particles) = 0;
    virtual std::shared_ptr<Camera> NewCamera() = 0;
    virtual std::shared_ptr<CoordSys> NewCoordSys() = 0;
    virtual std::shared_ptr<Glyphs> NewGlyphs() = 0;
    virtual std::shared_ptr<ParticlesRenderer> NewParticlesRenderer(std::shared_ptr<Particles> particles) = 0;
    virtual std::shared_ptr<PerspectiveProjection> NewPerspectiveProjection() = 0;
    virtual std::shared_ptr<TestTriangle> NewTestTriangle() = 0;
    virtual std::shared_ptr<TextConsole> NewTextConsole(int width, int height, float glyphWidth, float glyphHeight,
                                                        std::shared_ptr<Glyphs> glyphs) = 0;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_RENDERTARGETINTERFACE_H_

