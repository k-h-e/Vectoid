#ifndef VECTOID_SCENEGRAPH_OPENGL_RENDERTARGET_H_
#define VECTOID_SCENEGRAPH_OPENGL_RENDERTARGET_H_

#include <Vectoid/SceneGraph/RenderTargetInterface.h>

namespace Vectoid {
namespace SceneGraph {
//! <c>OpenGL</c> renderer.
namespace OpenGL {

//! <c>Vectoid</c> render target for rendering via <c>OpenGL</c>.
class RenderTarget : public virtual Vectoid::SceneGraph::RenderTargetInterface {
  public:
    RenderTarget();
    RenderTarget(const RenderTarget &other) = delete;
    RenderTarget &operator=(const RenderTarget &other) = delete;
    virtual void SetSceneGraph(const std::shared_ptr<SceneGraphNode> &sceneGraphRoot) override;
    virtual void RenderFrame() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::AgeColoredParticles> NewAgeColoredParticles(
        const std::shared_ptr<Core::Particles> &particles) override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::Camera> NewCamera() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::CoordSys> NewCoordSys() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::Geode> NewGeode(const std::shared_ptr<GeometryInterface> &geometry)
        override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::Glyphs> NewGlyphs() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::LineSegments> NewLineSegments(
        const std::shared_ptr<Core::LineSegmentProviderInterface> &lineSegmentProvider) override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::LitTriangles> NewLitTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider) override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::ParticlesRenderer> NewParticlesRenderer(
        const std::shared_ptr<Core::Particles> &particles) override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::PerspectiveProjection> NewPerspectiveProjection() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::SimpleLighting> NewSimpleLighting() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::TestTriangle> NewTestTriangle() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::TextConsole> NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const std::shared_ptr<SceneGraph::Glyphs> &glyphs)
        override;
    
  private:
    void initializeGL();

    std::shared_ptr<SceneGraphNode> sceneGraphRoot_;
    bool                            glInitialized_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_RENDERTARGET_H_
