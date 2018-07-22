#ifndef KXM_VECTOID_METAL_RENDERTARGET_H_
#define KXM_VECTOID_METAL_RENDERTARGET_H_

#include <kxm/Vectoid/RenderTargetInterface.h>

namespace kxm {
namespace Vectoid {
namespace Metal {

//! <c>Vectoid</c> render target for rendering via <c>Metal</c>.
/*!
 *  \ingroup VectoidMetal
 */
class RenderTarget : public virtual Vectoid::RenderTargetInterface {
  public:
    RenderTarget();
    RenderTarget(const RenderTarget &other) = delete;
    RenderTarget &operator=(const RenderTarget &other) = delete;
    virtual std::shared_ptr<AgeColoredParticles> NewAgeColoredParticles(std::shared_ptr<Particles> particles);
    virtual std::shared_ptr<Camera> NewCamera();
    virtual std::shared_ptr<CoordSys> NewCoordSys();
    virtual std::shared_ptr<Glyphs> NewGlyphs();
    virtual std::shared_ptr<ParticlesRenderer> NewParticlesRenderer(std::shared_ptr<Particles> particles);
    virtual std::shared_ptr<PerspectiveProjection> NewPerspectiveProjection();
    virtual std::shared_ptr<TestTriangle> NewTestTriangle();
    virtual std::shared_ptr<TextConsole> NewTextConsole(int width, int height, float glyphWidth, float glyphHeight,
                                                        std::shared_ptr<Vectoid::Glyphs> glyphs);
};

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_METAL_RENDERTARGET_H_

