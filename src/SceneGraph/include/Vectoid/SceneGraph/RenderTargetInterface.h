#ifndef VECTOID_SCENEGRAPH_RENDERTARGETINTERFACE_H_
#define VECTOID_SCENEGRAPH_RENDERTARGETINTERFACE_H_

#include <memory>
#include <K/Core/Interface.h>

namespace Vectoid {
namespace Core {
    class LineSegmentProviderInterface;
    class Particles;
    class TriangleProviderInterface;
}
}

namespace Vectoid {
namespace SceneGraph {

class AgeColoredParticles;
class Camera;
class CoordSys;
class GeometryInterface;
class Geode;
class Glyphs;
class LitTriangles;
class LineSegments;
class Node;
class ParticlesRenderer;
class PerspectiveProjection;
class SimpleLighting;
class TestTriangle;
class TextConsole;

//! Interface to <c>Vectoid</c> render targets.
/*!
 *  A <c>Vectoid</c> render target acts as rendering-platform-specific factory for scene graph nodes and associated
 *  resources.
 */
class RenderTargetInterface : public virtual K::Core::Interface {
  public:
    virtual void SetSceneGraph(const std::shared_ptr<Node> &sceneGraphRoot) = 0;
    //! Renders a frame using the current scene graph state.
    virtual void RenderFrame() = 0;
  
    virtual std::shared_ptr<::Vectoid::SceneGraph::AgeColoredParticles> NewAgeColoredParticles(
        const std::shared_ptr<Core::Particles> &particles) = 0;
    virtual std::shared_ptr<::Vectoid::SceneGraph::Camera> NewCamera() = 0;
    virtual std::shared_ptr<::Vectoid::SceneGraph::CoordSys> NewCoordSys() = 0;
    virtual std::shared_ptr<::Vectoid::SceneGraph::Geode> NewGeode(
        const std::shared_ptr<GeometryInterface> &geometry) = 0;
    virtual std::shared_ptr<::Vectoid::SceneGraph::Glyphs> NewGlyphs() = 0;
    virtual std::shared_ptr<::Vectoid::SceneGraph::LineSegments> NewLineSegments(
        const std::shared_ptr<Core::LineSegmentProviderInterface> &lineSegmentProvider) = 0;
    virtual std::shared_ptr<::Vectoid::SceneGraph::LitTriangles> NewLitTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider) = 0;
    virtual std::shared_ptr<::Vectoid::SceneGraph::ParticlesRenderer> NewParticlesRenderer(
        const std::shared_ptr<Core::Particles> &particles) = 0;
    virtual std::shared_ptr<::Vectoid::SceneGraph::PerspectiveProjection> NewPerspectiveProjection() = 0;
    virtual std::shared_ptr<::Vectoid::SceneGraph::SimpleLighting> NewSimpleLighting() = 0;
    virtual std::shared_ptr<::Vectoid::SceneGraph::TestTriangle> NewTestTriangle() = 0;
    virtual std::shared_ptr<::Vectoid::SceneGraph::TextConsole> NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const std::shared_ptr<Glyphs> &glyphs) = 0;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_RENDERTARGETINTERFACE_H_

