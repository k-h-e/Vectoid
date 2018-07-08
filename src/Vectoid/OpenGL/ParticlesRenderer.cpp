#include <kxm/Vectoid/OpenGL/ParticlesRenderer.h>

#include <kxm/Vectoid/Particles.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;

namespace kxm {
namespace Vectoid {
namespace OpenGL {

ParticlesRenderer::ParticlesRenderer(shared_ptr<Particles> particles)
        : Vectoid::ParticlesRenderer(particles) {
    // Nop.
}

void ParticlesRenderer::Render() {
    int num = particles_->Count();
    if (num == 0)
        return;
    if (num > (int)vertexBuffer_.size() / 3)
        vertexBuffer_.resize(num * 3);
        // See to it we have enough buffer space for all particles. The whole space might not be
        // needed, though, as particles can be hidden.
    
    GLfloat *ptr        = &vertexBuffer_[0];
    int     numToRender = 0;
    for (Particles::ParticleInfo &particle : particles_->Iterate()) {
        if (particle.hidden) {
            continue;
        }
        *ptr++ = particle.position.x;
        *ptr++ = particle.position.y;
        *ptr++ = particle.position.z;
        numToRender++;
    }

    if (numToRender) {
        glPointSize(3.0f);
        glVertexPointer(3, GL_FLOAT, 0, &vertexBuffer_[0]);
   	    glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_POINTS, 0, numToRender);
        glDisableClientState(GL_VERTEX_ARRAY);
        glPointSize(1.0f);
    }
}

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.
