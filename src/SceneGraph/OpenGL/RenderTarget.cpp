#include <Vectoid/SceneGraph/OpenGL/RenderTarget.h>

#include <Vectoid/SceneGraph/RenderVisitor.h>
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

void RenderTarget::SetSceneGraph(const std::shared_ptr<Node> &sceneGraphRoot) {
    sceneGraphRoot_ = sceneGraphRoot;
}

void RenderTarget::RenderFrame() {
    if (!glInitialized_) {
        initializeGL();
        glInitialized_ = true;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (sceneGraphRoot_) {
        RenderVisitor renderVisitor;
        sceneGraphRoot_->Visit(&renderVisitor);
    }
}

shared_ptr<::Vectoid::SceneGraph::AgeColoredParticles> RenderTarget::NewAgeColoredParticles(
        const shared_ptr<Particles> &particles) {
    return shared_ptr<OpenGL::AgeColoredParticles>(new AgeColoredParticles(particles));
}

shared_ptr<::Vectoid::SceneGraph::Camera> RenderTarget::NewCamera() {
    return shared_ptr<OpenGL::Camera>(new Camera());
}

shared_ptr<::Vectoid::SceneGraph::CoordSys> RenderTarget::NewCoordSys() {
    return shared_ptr<OpenGL::CoordSys>(new CoordSys());
}

shared_ptr<::Vectoid::SceneGraph::Geode> RenderTarget::NewGeode(const std::shared_ptr<GeometryInterface> &geometry) {
    return shared_ptr<OpenGL::Geode>(new Geode(geometry));
}

shared_ptr<::Vectoid::SceneGraph::Glyphs> RenderTarget::NewGlyphs() {
    return shared_ptr<OpenGL::Glyphs>(new Glyphs());
}

shared_ptr<::Vectoid::SceneGraph::LineSegments> RenderTarget::NewLineSegments(
        const shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider) {
    return make_shared<OpenGL::LineSegments>(lineSegmentProvider);
}

shared_ptr<::Vectoid::SceneGraph::LitTriangles> RenderTarget::NewLitTriangles(
        const shared_ptr<TriangleProviderInterface> &triangleProvider) {
    return make_shared<OpenGL::LitTriangles>(triangleProvider);
}

shared_ptr<::Vectoid::SceneGraph::ParticlesRenderer> RenderTarget::NewParticlesRenderer(
        const shared_ptr<Particles> &particles) {
    return shared_ptr<OpenGL::ParticlesRenderer>(new ParticlesRenderer(particles));
}

shared_ptr<::Vectoid::SceneGraph::PerspectiveProjection> RenderTarget::NewPerspectiveProjection() {
    return shared_ptr<OpenGL::PerspectiveProjection>(new PerspectiveProjection());
}

shared_ptr<::Vectoid::SceneGraph::SimpleLighting> RenderTarget::NewSimpleLighting() {
    return make_shared<OpenGL::SimpleLighting>();
}

shared_ptr<::Vectoid::SceneGraph::TestTriangle> RenderTarget::NewTestTriangle() {
    return shared_ptr<OpenGL::TestTriangle>(new TestTriangle());
}

shared_ptr<::Vectoid::SceneGraph::TextConsole> RenderTarget::NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const shared_ptr<SceneGraph::Glyphs> &glyphs) {
    return shared_ptr<OpenGL::TextConsole>(new TextConsole(width, height, glyphWidth, glyphHeight, glyphs));
}

void RenderTarget::initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

