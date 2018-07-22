#ifndef KXM_VECTOID_OPENGL_RENDERTARGET_H_
#define KXM_VECTOID_OPENGL_RENDERTARGET_H_

#include <kxm/Vectoid/RenderTargetInterface.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

//! <c>Vectoid</c> render target for rendering via <c>OpenGL</c>.
/*!
 *  \ingroup VectoidOpenGL
 */
class RenderTarget : public virtual Vectoid::RenderTargetInterface {
  public:
    RenderTarget();
    RenderTarget(const RenderTarget &other) = delete;
    RenderTarget &operator=(const RenderTarget &other) = delete;
    virtual void SetSceneGraph(const std::shared_ptr<SceneGraphNode> &sceneGraphRoot);
    virtual void RenderFrame();
    virtual std::shared_ptr<AgeColoredParticles> NewAgeColoredParticles(const std::shared_ptr<Particles> &particles);
    virtual std::shared_ptr<Camera> NewCamera();
    virtual std::shared_ptr<CoordSys> NewCoordSys();
    virtual std::shared_ptr<Glyphs> NewGlyphs();
    virtual std::shared_ptr<ParticlesRenderer> NewParticlesRenderer(const std::shared_ptr<Particles> &particles);
    virtual std::shared_ptr<PerspectiveProjection> NewPerspectiveProjection();
    virtual std::shared_ptr<TestTriangle> NewTestTriangle();
    virtual std::shared_ptr<TextConsole> NewTextConsole(int width, int height, float glyphWidth, float glyphHeight,
                                                        const std::shared_ptr<Vectoid::Glyphs> &glyphs);
    
  private:
    std::shared_ptr<SceneGraphNode> sceneGraphRoot_;
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_OPENGL_RENDERTARGET_H_
