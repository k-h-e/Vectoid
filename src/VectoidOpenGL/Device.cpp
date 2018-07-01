#include <kxm/VectoidOpenGL/Device.h>

#include <kxm/VectoidOpenGL/AgeColoredParticles.h>
#include <kxm/VectoidOpenGL/Camera.h>
#include <kxm/VectoidOpenGL/CoordSys.h>
#include <kxm/VectoidOpenGL/Glyphs.h>
#include <kxm/VectoidOpenGL/PerspectiveProjection.h>
#include <kxm/VectoidOpenGL/TestTriangle.h>
#include <kxm/VectoidOpenGL/TextConsole.h>

using std::shared_ptr;

namespace kxm {
namespace Vectoid {
namespace OpenGL {

shared_ptr<Vectoid::AgeColoredParticles> Device::newAgeColoredParticles() {
    return std::make_shared<AgeColoredParticles>();
}

shared_ptr<Vectoid::Camera> Device::newCamera() {
    return std::make_shared<Camera>();
}

shared_ptr<Vectoid::CoordSys> Device::newCoordSys() {
    return std::make_shared<CoordSys>();
}

shared_ptr<Vectoid::Glyphs> Device::newGlyphs() {
    return std::make_shared<Glyphs>();
}

shared_ptr<Vectoid::ParticlesRenderer> Device::newParticlesRenderer(shared_ptr<Particles> particles) {
    return std::make_shared<ParticlesRenderer>(particles);
}

shared_ptr<Vectoid::PerspectiveProjection> Device::newPerspectiveProjection() {
    return std::make_shared<PerspectiveProjection>();
}

shared_ptr<Vectoid::TestTriangle> Device::newTestTriangle() {
    return std::make_shared<TestTriangle>();
}

shared_ptr<Vectoid::TextConsole> Device::newTextConsole(int width, int height, float glyphWidth, float glyphHeight,
                                                        shared_ptr<Vectoid::Glyphs> glyphs) {
    return std::make_shared<TextConsole>(width, height, glyphWidth, glyphHeight, glyphs);
}

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.

