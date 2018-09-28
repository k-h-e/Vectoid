#include <kxm/Vectoid/Vulkan/RenderTarget.h>

#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Vulkan/AgeColoredParticles.h>
#include <kxm/Vectoid/Vulkan/Camera.h>
#include <kxm/Vectoid/Vulkan/Context.h>
#include <kxm/Vectoid/Vulkan/CoordSys.h>
#include <kxm/Vectoid/Vulkan/Glyphs.h>
#include <kxm/Vectoid/Vulkan/ParticlesRenderer.h>
#include <kxm/Vectoid/Vulkan/PerspectiveProjection.h>
#include <kxm/Vectoid/Vulkan/TestTriangle.h>
#include <kxm/Vectoid/Vulkan/TextConsole.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

RenderTarget::RenderTarget() {
    context_ = make_shared<Context>();
}

void RenderTarget::SetSceneGraph(const std::shared_ptr<SceneGraphNode> &sceneGraphRoot) {
    sceneGraphRoot_ = sceneGraphRoot;
}

void RenderTarget::RenderFrame() {
}

shared_ptr<Vectoid::AgeColoredParticles> RenderTarget::NewAgeColoredParticles(const shared_ptr<Particles> &particles) {
    return make_shared<AgeColoredParticles>(context_, particles);
}

shared_ptr<Vectoid::Camera> RenderTarget::NewCamera() {
    return make_shared<Camera>(context_);
}

shared_ptr<Vectoid::CoordSys> RenderTarget::NewCoordSys() {
    return make_shared<CoordSys>(context_);
}

shared_ptr<Vectoid::Geode> RenderTarget::NewGeode(const std::shared_ptr<GeometryInterface> &geometry) {
    return make_shared<Geode>(geometry);
}

shared_ptr<Vectoid::Glyphs> RenderTarget::NewGlyphs() {
    return shared_ptr<Glyphs>(new Glyphs(context_));
}

shared_ptr<Vectoid::ParticlesRenderer> RenderTarget::NewParticlesRenderer(const shared_ptr<Particles> &particles) {
    return make_shared<ParticlesRenderer>(context_, particles);
}

shared_ptr<Vectoid::PerspectiveProjection> RenderTarget::NewPerspectiveProjection() {
    return make_shared<PerspectiveProjection>(context_);
}

shared_ptr<Vectoid::TestTriangle> RenderTarget::NewTestTriangle() {
    return make_shared<TestTriangle>(context_);
}

shared_ptr<Vectoid::TextConsole> RenderTarget::NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const shared_ptr<Vectoid::Glyphs> &glyphs) {
    return make_shared<TextConsole>(context_, width, height, glyphWidth, glyphHeight, glyphs);
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

