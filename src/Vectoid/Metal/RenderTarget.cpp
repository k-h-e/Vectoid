#include <kxm/Vectoid/Metal/RenderTarget.h>

#include <kxm/Vectoid/Metal/AgeColoredParticles.h>
#include <kxm/Vectoid/Metal/Camera.h>
#include <kxm/Vectoid/Metal/CoordSys.h>
#include <kxm/Vectoid/Metal/Glyphs.h>
#include <kxm/Vectoid/Metal/ParticlesRenderer.h>
#include <kxm/Vectoid/Metal/PerspectiveProjection.h>
#include <kxm/Vectoid/Metal/TestTriangle.h>
#include <kxm/Vectoid/Metal/TextConsole.h>

using std::shared_ptr;

namespace kxm {
namespace Vectoid {
namespace Metal {

RenderTarget::RenderTarget() {
    // Nop.
}

shared_ptr<Vectoid::AgeColoredParticles> RenderTarget::NewAgeColoredParticles(shared_ptr<Particles> particles) {
    return std::make_shared<AgeColoredParticles>(particles);
}

shared_ptr<Vectoid::Camera> RenderTarget::NewCamera() {
    return std::make_shared<Camera>();
}

shared_ptr<Vectoid::CoordSys> RenderTarget::NewCoordSys() {
    return std::make_shared<CoordSys>();
}

shared_ptr<Vectoid::Glyphs> RenderTarget::NewGlyphs() {
    return std::make_shared<Glyphs>();
}

shared_ptr<Vectoid::ParticlesRenderer> RenderTarget::NewParticlesRenderer(shared_ptr<Particles> particles) {
    return std::make_shared<ParticlesRenderer>(particles);
}

shared_ptr<Vectoid::PerspectiveProjection> RenderTarget::NewPerspectiveProjection() {
    return std::make_shared<PerspectiveProjection>();
}

shared_ptr<Vectoid::TestTriangle> RenderTarget::NewTestTriangle() {
    return std::make_shared<TestTriangle>();
}

shared_ptr<Vectoid::TextConsole> RenderTarget::NewTextConsole(int width, int height, float glyphWidth,
                                                              float glyphHeight, shared_ptr<Vectoid::Glyphs> glyphs) {
    return std::make_shared<TextConsole>(width, height, glyphWidth, glyphHeight, glyphs);
}

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.

