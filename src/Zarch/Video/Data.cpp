#include <kxm/Zarch/Video/Data.h>

#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/Particles.h>

using namespace std;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

void Data::StartParticleExplosion(const Vectoid::Vector &position, int particleCount) {
    particleCount >>= 1;
    for (int i = 0; i < particleCount; ++i) {
        Particles::ParticleInfo *particle      = &thrusterParticles->Add(Vector(), Vector()),
                                *otherParticle = &thrusterParticles->Add(Vector(), Vector());
        for (int j = 0; j < 2; j++) {
            if (j) {
                Particles::ParticleInfo *tmp = particle;
                particle = otherParticle;
                otherParticle = tmp;
            }
            Vector direction(1.0f, 0.0f, 0.0f);
            Transform transform(YAxis, particle->random0 * 180.0f);
            transform.Prepend(Transform(ZAxis, particle->random1 * 90.0f));
            transform.ApplyTo(&direction);
            particle->position = position + (0.5f * (otherParticle->random0 + 1.0f) * .5f) * direction;
            particle->velocity = (1.0f + (0.5f * (otherParticle->random1 + 1.0f)) * 1.5f) * direction;
        }
    }
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
