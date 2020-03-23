#include <kxm/Vectoid/OpenGL/RenderTarget.h>

#include <kxm/Vectoid/OpenGL/AgeColoredParticles.h>
#include <kxm/Vectoid/OpenGL/Camera.h>
#include <kxm/Vectoid/OpenGL/CoordSys.h>
#include <kxm/Vectoid/OpenGL/Geode.h>
#include <kxm/Vectoid/OpenGL/Glyphs.h>
#include <kxm/Vectoid/OpenGL/LitTriangles.h>
#include <kxm/Vectoid/OpenGL/ParticlesRenderer.h>
#include <kxm/Vectoid/OpenGL/PerspectiveProjection.h>
#include <kxm/Vectoid/OpenGL/SimpleLighting.h>
#include <kxm/Vectoid/OpenGL/TestTriangle.h>
#include <kxm/Vectoid/OpenGL/TextConsole.h>

using namespace std;

namespace kxm {
namespace Vectoid {
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

shared_ptr<Vectoid::AgeColoredParticles> RenderTarget::NewAgeColoredParticles(const shared_ptr<Particles> &particles) {
    return shared_ptr<AgeColoredParticles>(new AgeColoredParticles(particles));
}

shared_ptr<Vectoid::Camera> RenderTarget::NewCamera() {
    return shared_ptr<Camera>(new Camera());
}

shared_ptr<Vectoid::CoordSys> RenderTarget::NewCoordSys() {
    return shared_ptr<CoordSys>(new CoordSys());
}

shared_ptr<Vectoid::Geode> RenderTarget::NewGeode(const std::shared_ptr<GeometryInterface> &geometry) {
    return shared_ptr<Geode>(new Geode(geometry));
}

shared_ptr<Vectoid::Glyphs> RenderTarget::NewGlyphs() {
    return shared_ptr<Glyphs>(new Glyphs());
}

shared_ptr<Vectoid::LitTriangles> RenderTarget::NewLitTriangles(
        const shared_ptr<TriangleProviderInterface> &triangleProvider) {
    return make_shared<LitTriangles>(triangleProvider);
}

shared_ptr<Vectoid::ParticlesRenderer> RenderTarget::NewParticlesRenderer(const shared_ptr<Particles> &particles) {
    return shared_ptr<ParticlesRenderer>(new ParticlesRenderer(particles));
}

shared_ptr<Vectoid::PerspectiveProjection> RenderTarget::NewPerspectiveProjection() {
    return shared_ptr<PerspectiveProjection>(new PerspectiveProjection());
}

shared_ptr<Vectoid::SimpleLighting> RenderTarget::NewSimpleLighting() {
    return make_shared<SimpleLighting>();
}

shared_ptr<Vectoid::TestTriangle> RenderTarget::NewTestTriangle() {
    return shared_ptr<TestTriangle>(new TestTriangle());
}

shared_ptr<Vectoid::TextConsole> RenderTarget::NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const shared_ptr<Vectoid::Glyphs> &glyphs) {
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
}    // Namespace Vectoid.
}    // Namespace kxm.

