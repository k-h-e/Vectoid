#ifndef KXM_VECTOID_VULKAN_RENDERTARGET_H_
#define KXM_VECTOID_VULKAN_RENDERTARGET_H_

#include <kxm/Vectoid/RenderTargetInterface.h>

namespace kxm {
namespace Vectoid {
namespace Vulkan {

class Context;

//! <c>Vectoid</c> render target for rendering via <c>Vulkan</c>.
/*!
 *  \ingroup VectoidVulkan
 */
class RenderTarget : public virtual Vectoid::RenderTargetInterface {
  public:
    RenderTarget();
    RenderTarget(const RenderTarget &other) = delete;
    RenderTarget &operator=(const RenderTarget &other) = delete;
    virtual void SetSceneGraph(const std::shared_ptr<SceneGraphNode> &sceneGraphRoot);
    virtual void RenderFrame();
    virtual std::shared_ptr<Vectoid::AgeColoredParticles> NewAgeColoredParticles(
        const std::shared_ptr<Particles> &particles);
    virtual std::shared_ptr<Vectoid::Camera> NewCamera();
    virtual std::shared_ptr<Vectoid::CoordSys> NewCoordSys();
    virtual std::shared_ptr<Vectoid::Geode> NewGeode(const std::shared_ptr<GeometryInterface> &geometry);
    virtual std::shared_ptr<Vectoid::Glyphs> NewGlyphs();
    virtual std::shared_ptr<Vectoid::ParticlesRenderer> NewParticlesRenderer(
        const std::shared_ptr<Particles> &particles);
    virtual std::shared_ptr<Vectoid::PerspectiveProjection> NewPerspectiveProjection();
    virtual std::shared_ptr<Vectoid::TestTriangle> NewTestTriangle();
    virtual std::shared_ptr<Vectoid::TextConsole> NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const std::shared_ptr<Vectoid::Glyphs> &glyphs);
    
  protected:
    std::shared_ptr<Context> context_;
    
  private:
    std::shared_ptr<SceneGraphNode> sceneGraphRoot_;
};

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_VULKAN_RENDERTARGET_H_

