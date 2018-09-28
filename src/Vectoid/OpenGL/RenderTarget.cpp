#include <kxm/Vectoid/OpenGL/RenderTarget.h>

#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/OpenGL/AgeColoredParticles.h>
#include <kxm/Vectoid/OpenGL/Camera.h>
#include <kxm/Vectoid/OpenGL/CoordSys.h>
#include <kxm/Vectoid/OpenGL/Glyphs.h>
#include <kxm/Vectoid/OpenGL/ParticlesRenderer.h>
#include <kxm/Vectoid/OpenGL/PerspectiveProjection.h>
#include <kxm/Vectoid/OpenGL/TestTriangle.h>
#include <kxm/Vectoid/OpenGL/TextConsole.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace OpenGL {

RenderTarget::RenderTarget() {
    // Nop.
}

void RenderTarget::SetSceneGraph(const std::shared_ptr<SceneGraphNode> &sceneGraphRoot) {
    sceneGraphRoot_ = sceneGraphRoot;
}

void RenderTarget::RenderFrame() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (sceneGraphRoot_) {
        sceneGraphRoot_->Render();
    }
}

shared_ptr<Vectoid::AgeColoredParticles> RenderTarget::NewAgeColoredParticles(const shared_ptr<Particles> &particles) {
    return make_shared<AgeColoredParticles>(particles);
}

shared_ptr<Vectoid::Camera> RenderTarget::NewCamera() {
    return make_shared<Camera>();
}

shared_ptr<Vectoid::CoordSys> RenderTarget::NewCoordSys() {
    return make_shared<CoordSys>();
}

shared_ptr<Vectoid::Geode> RenderTarget::NewGeode(const std::shared_ptr<GeometryInterface> &geometry) {
    return shared_ptr<Geode>(new Geode(geometry));
}

shared_ptr<Vectoid::Glyphs> RenderTarget::NewGlyphs() {
    return make_shared<Glyphs>();
}

shared_ptr<Vectoid::ParticlesRenderer> RenderTarget::NewParticlesRenderer(const shared_ptr<Particles> &particles) {
    return make_shared<ParticlesRenderer>(particles);
}

shared_ptr<Vectoid::PerspectiveProjection> RenderTarget::NewPerspectiveProjection() {
    return make_shared<PerspectiveProjection>();
}

shared_ptr<Vectoid::TestTriangle> RenderTarget::NewTestTriangle() {
    return make_shared<TestTriangle>();
}

shared_ptr<Vectoid::TextConsole> RenderTarget::NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const shared_ptr<Vectoid::Glyphs> &glyphs) {
    return make_shared<TextConsole>(width, height, glyphWidth, glyphHeight, glyphs);
}

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.
