#include <Vectoid/SceneGraph/ParticlesRenderer.h>

using namespace std;
using Vectoid::Core::Particles;


namespace Vectoid {
namespace SceneGraph {

ParticlesRenderer::ParticlesRenderer(const shared_ptr<Particles> &particles)
        : particles_(particles) {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
