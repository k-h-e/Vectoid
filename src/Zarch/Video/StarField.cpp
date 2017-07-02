#include <kxm/Zarch/Video/StarField.h>

#include <random>
#include <kxm/Core/ReusableItems.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Zarch/MapParameters.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

struct Data;

StarField::StarField(shared_ptr<Data> videoData, shared_ptr<Vectoid::Particles> particles)
        : data_(videoData),
          particles_(particles) {
    Data                       &data     = *data_;
    const int                  randomMax = 10000;
    default_random_engine      randomEngine;
    uniform_int_distribution<> randomDistribution(0, randomMax);
    for (int i = 0; i < data.mapParameters->numStars; i++) {
        float t = (float)randomDistribution(randomEngine) / (float)randomMax;
        float x = data.mapParameters->starFieldCoordRange.AffineCombination(t);
        data.mapParameters->starFieldCoordRange.Clamp(&x);
        t = (float)randomDistribution(randomEngine) / (float)randomMax;
        float y = data.mapParameters->starFieldCoordRange.AffineCombination(t);
        data.mapParameters->starFieldCoordRange.Clamp(&y);
        t = (float)randomDistribution(randomEngine) / (float)randomMax;
        float z = data.mapParameters->starFieldCoordRange.AffineCombination(t);
        data.mapParameters->starFieldCoordRange.Clamp(&z);
        particles_->Add(Vector(x, y, z), Vector());
    }
}

void StarField::ExecuteAction() {
    Data   &data = *data_;
    Vector base  = data.camera->Position();
    for (Particles::ParticleInfo &particle : particles_->Iterate()) {
        Vector position = particle.position;
        Range xRange(data.mapParameters->starFieldCoordRange, base.x);
        xRange.ClampModulo(&position.x);
        Range yRange(data.mapParameters->starFieldCoordRange, base.y);
        yRange.ClampModulo(&position.y);
        Range zRange(data.mapParameters->starFieldCoordRange, base.z);
        zRange.ClampModulo(&position.z);
        particle.position = position;
        particle.hidden   = (position.y < data.mapParameters->starFieldMinHeight);
    }
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
