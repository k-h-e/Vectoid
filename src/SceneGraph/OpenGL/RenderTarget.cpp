#include <Vectoid/SceneGraph/OpenGL/RenderTarget.h>

#include <Vectoid/SceneGraph/OpenGL/AgeColoredParticles.h>
#include <Vectoid/SceneGraph/OpenGL/Camera.h>
#include <Vectoid/SceneGraph/OpenGL/CoordSys.h>
#include <Vectoid/SceneGraph/OpenGL/Geode.h>
#include <Vectoid/SceneGraph/OpenGL/Glyphs.h>
#include <Vectoid/SceneGraph/OpenGL/LineSegments.h>
#include <Vectoid/SceneGraph/OpenGL/LitTriangles.h>
#include <Vectoid/SceneGraph/OpenGL/ParticlesRenderer.h>
#include <Vectoid/SceneGraph/OpenGL/PerspectiveProjection.h>
#include <Vectoid/SceneGraph/OpenGL/SimpleLighting.h>
#include <Vectoid/SceneGraph/OpenGL/TestTriangle.h>
#include <Vectoid/SceneGraph/OpenGL/TextConsole.h>

using namespace std;
using Vectoid::Core::LineSegmentProviderInterface;
using Vectoid::Core::Particles;
using Vectoid::Core::TriangleProviderInterface;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

RenderTarget::RenderTarget()
        : glInitialized_(false) {
    // Nop.
}

void RenderTarget::SetSceneGraph(const std::shared_ptr<SceneGraphNode> &sceneGraphRoot) {
    sceneGraphRoot_ = sceneGraphRoot;
}

void RenderTarget::RenderFrame() {
    if (!glInitialized_) {
        initializeGL();
        glInitialized_ = true;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (sceneGraphRoot_) {
        sceneGraphRoot_->Render();
    }
}

shared_ptr<SceneGraph::AgeColoredParticles> RenderTarget::NewAgeColoredParticles(
        const shared_ptr<Particles> &particles) {
    return shared_ptr<AgeColoredParticles>(new AgeColoredParticles(particles));
}

shared_ptr<SceneGraph::Camera> RenderTarget::NewCamera() {
    return shared_ptr<Camera>(new Camera());
}

shared_ptr<SceneGraph::CoordSys> RenderTarget::NewCoordSys() {
    return shared_ptr<CoordSys>(new CoordSys());
}

shared_ptr<SceneGraph::Geode> RenderTarget::NewGeode(const std::shared_ptr<GeometryInterface> &geometry) {
    return shared_ptr<Geode>(new Geode(geometry));
}

shared_ptr<SceneGraph::Glyphs> RenderTarget::NewGlyphs() {
    return shared_ptr<Glyphs>(new Glyphs());
}

shared_ptr<SceneGraph::LineSegments> RenderTarget::NewLineSegments(
        const shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider) {
    return make_shared<LineSegments>(lineSegmentProvider);
}

shared_ptr<SceneGraph::LitTriangles> RenderTarget::NewLitTriangles(
        const shared_ptr<TriangleProviderInterface> &triangleProvider) {
    return make_shared<LitTriangles>(triangleProvider);
}

shared_ptr<SceneGraph::ParticlesRenderer> RenderTarget::NewParticlesRenderer(const shared_ptr<Particles> &particles) {
    return shared_ptr<ParticlesRenderer>(new ParticlesRenderer(particles));
}

shared_ptr<SceneGraph::PerspectiveProjection> RenderTarget::NewPerspectiveProjection() {
    return shared_ptr<PerspectiveProjection>(new PerspectiveProjection());
}

shared_ptr<SceneGraph::SimpleLighting> RenderTarget::NewSimpleLighting() {
    return make_shared<SimpleLighting>();
}

shared_ptr<SceneGraph::TestTriangle> RenderTarget::NewTestTriangle() {
    return shared_ptr<TestTriangle>(new TestTriangle());
}

shared_ptr<SceneGraph::TextConsole> RenderTarget::NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const shared_ptr<SceneGraph::Glyphs> &glyphs) {
    return shared_ptr<TextConsole>(new TextConsole(width, height, glyphWidth, glyphHeight, glyphs));
}

void RenderTarget::initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

