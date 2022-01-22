#ifndef VECTOID_SCENEGRAPH_OPENGL_RENDERTARGET_H_
#define VECTOID_SCENEGRAPH_OPENGL_RENDERTARGET_H_

#include <Vectoid/SceneGraph/RenderTargetInterface.h>

namespace Vectoid {
namespace SceneGraph {
//! <c>OpenGL</c> renderer.
namespace OpenGL {

class Context;

//! <c>Vectoid</c> render target for rendering via <c>OpenGL</c>.
class RenderTarget : public virtual Vectoid::SceneGraph::RenderTargetInterface {
  public:
    RenderTarget()                                     = delete;
    RenderTarget(const std::shared_ptr<Context> &context);
    RenderTarget(const RenderTarget &other)            = delete;
    RenderTarget &operator=(const RenderTarget &other) = delete;
    RenderTarget(RenderTarget &&other)                 = delete;
    RenderTarget &operator=(RenderTarget &&other)      = delete;

    void SetSceneGraph(const std::shared_ptr<TreeNode> &sceneGraphRoot) override;
    void RenderFrame() override;
    std::shared_ptr<::Vectoid::SceneGraph::AgeColoredParticles> NewAgeColoredParticles(
        const std::shared_ptr<Core::Particles> &particles) override;
    std::shared_ptr<::Vectoid::SceneGraph::Camera> NewCamera() override;
    std::shared_ptr<::Vectoid::SceneGraph::CoordSys> NewCoordSys() override;
    std::shared_ptr<::Vectoid::SceneGraph::Geode> NewGeode(const std::shared_ptr<Geometry> &geometry) override;
    std::shared_ptr<::Vectoid::SceneGraph::Glyphs> NewGlyphs() override;
    std::shared_ptr<::Vectoid::SceneGraph::LineSegments> NewLineSegments(
        const std::shared_ptr<Core::LineSegmentProviderInterface> &lineSegmentProvider) override;
    std::shared_ptr<::Vectoid::SceneGraph::LitColorCodedTriangles> NewLitColorCodedTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider) override;
    std::shared_ptr<::Vectoid::SceneGraph::LitTriangles> NewLitTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider) override;
    std::shared_ptr<::Vectoid::SceneGraph::ParticlesRenderer> NewParticlesRenderer(
        const std::shared_ptr<Core::Particles> &particles) override;
    std::shared_ptr<::Vectoid::SceneGraph::PerspectiveProjection> NewPerspectiveProjection() override;
    std::shared_ptr<::Vectoid::SceneGraph::Points> NewPoints(
        const std::shared_ptr<DataSet::Points> &points) override;
    std::shared_ptr<::Vectoid::SceneGraph::SimpleGeometryRenderer> NewSimpleGeometryRenderer(
        const std::shared_ptr<::Vectoid::SceneGraph::SimpleGeometry> &geometry) override;
    std::shared_ptr<::Vectoid::SceneGraph::SimpleLighting> NewSimpleLighting() override;
    std::shared_ptr<::Vectoid::SceneGraph::TerrainRenderer> NewTerrainRenderer(
        const std::shared_ptr<::Vectoid::SceneGraph::Terrain> &terrain,
        const std::shared_ptr<::Vectoid::SceneGraph::MapParameters> &mapParameters) override;
    std::shared_ptr<::Vectoid::SceneGraph::TestTriangle> NewTestTriangle() override;
    std::shared_ptr<::Vectoid::SceneGraph::TextConsole> NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const std::shared_ptr<SceneGraph::Glyphs> &glyphs)
        override;
    std::shared_ptr<::Vectoid::SceneGraph::TransparentTriangles> NewTransparentTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider) override;
    
  private:
    std::shared_ptr<Context>  context_;
    std::shared_ptr<TreeNode> sceneGraphRoot_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_RENDERTARGET_H_
