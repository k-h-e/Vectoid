#ifndef VECTOID_SCENEGRAPH_OPENGL_RENDERTARGET_H_
#define VECTOID_SCENEGRAPH_OPENGL_RENDERTARGET_H_

#include <Vectoid/SceneGraph/RenderTargetInterface.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

//! <c>Vectoid</c> render target for rendering via <c>OpenGL</c>.
/*!
 *  \ingroup VectoidOpenGL
 */
class RenderTarget : public virtual Vectoid::SceneGraph::RenderTargetInterface {
  public:
    RenderTarget();
    RenderTarget(const RenderTarget &other) = delete;
    RenderTarget &operator=(const RenderTarget &other) = delete;
    virtual void SetSceneGraph(const std::shared_ptr<SceneGraphNode> &sceneGraphRoot);
    virtual void RenderFrame();
    virtual std::shared_ptr<SceneGraph::AgeColoredParticles> NewAgeColoredParticles(
        const std::shared_ptr<Core::Particles> &particles);
    virtual std::shared_ptr<SceneGraph::Camera> NewCamera();
    virtual std::shared_ptr<SceneGraph::CoordSys> NewCoordSys();
    virtual std::shared_ptr<SceneGraph::Geode> NewGeode(const std::shared_ptr<GeometryInterface> &geometry);
    virtual std::shared_ptr<SceneGraph::Glyphs> NewGlyphs();
    virtual std::shared_ptr<SceneGraph::LineSegments> NewLineSegments(
        const std::shared_ptr<Core::LineSegmentProviderInterface> &lineSegmentProvider);
    virtual std::shared_ptr<SceneGraph::LitTriangles> NewLitTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);
    virtual std::shared_ptr<SceneGraph::ParticlesRenderer> NewParticlesRenderer(
        const std::shared_ptr<Core::Particles> &particles);
    virtual std::shared_ptr<SceneGraph::PerspectiveProjection> NewPerspectiveProjection();
    virtual std::shared_ptr<SceneGraph::SimpleLighting> NewSimpleLighting();
    virtual std::shared_ptr<SceneGraph::TestTriangle> NewTestTriangle();
    virtual std::shared_ptr<SceneGraph::TextConsole> NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const std::shared_ptr<SceneGraph::Glyphs> &glyphs);
    
  private:
    void initializeGL();

    std::shared_ptr<SceneGraphNode> sceneGraphRoot_;
    bool                            glInitialized_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_RENDERTARGET_H_
