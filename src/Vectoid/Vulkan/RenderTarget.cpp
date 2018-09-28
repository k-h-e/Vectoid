#include <kxm/Vectoid/Vulkan/RenderTarget.h>

#include <kxm/Vectoid/Vulkan/AgeColoredParticles.h>
#include <kxm/Vectoid/Vulkan/Camera.h>
#include <kxm/Vectoid/Vulkan/Context.h>
#include <kxm/Vectoid/Vulkan/CoordSys.h>
#include <kxm/Vectoid/Vulkan/Geode.h>
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
    return shared_ptr<AgeColoredParticles>(new AgeColoredParticles(context_, particles));
}

shared_ptr<Vectoid::Camera> RenderTarget::NewCamera() {
    return shared_ptr<Camera>(new Camera(context_));
}

shared_ptr<Vectoid::CoordSys> RenderTarget::NewCoordSys() {
    return shared_ptr<CoordSys>(new CoordSys(context_));
}

shared_ptr<Vectoid::Geode> RenderTarget::NewGeode(const std::shared_ptr<GeometryInterface> &geometry) {
    return shared_ptr<Geode>(new Geode(geometry));
}

shared_ptr<Vectoid::Glyphs> RenderTarget::NewGlyphs() {
    return shared_ptr<Glyphs>(new Glyphs(context_));
}

shared_ptr<Vectoid::ParticlesRenderer> RenderTarget::NewParticlesRenderer(const shared_ptr<Particles> &particles) {
    return shared_ptr<ParticlesRenderer>(new ParticlesRenderer(context_, particles));
}

shared_ptr<Vectoid::PerspectiveProjection> RenderTarget::NewPerspectiveProjection() {
    return shared_ptr<PerspectiveProjection>(new PerspectiveProjection(context_));
}

shared_ptr<Vectoid::TestTriangle> RenderTarget::NewTestTriangle() {
    return shared_ptr<TestTriangle>(new TestTriangle(context_));
}

shared_ptr<Vectoid::TextConsole> RenderTarget::NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const shared_ptr<Vectoid::Glyphs> &glyphs) {
    return shared_ptr<TextConsole>(new TextConsole(context_, width, height, glyphWidth, glyphHeight, glyphs));
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.

