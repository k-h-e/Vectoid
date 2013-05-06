//
//  NewStarFieldProcess.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/30/13.
//
//


#include <kxm/Zarch/Video/StarFieldProcess.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <kxm/Core/ReusableItems.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Zarch/MapParameters.h>


using namespace boost;
using namespace kxm::Core;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

StarFieldProcess::StarFieldProcess(shared_ptr<Video::Data> videoData,
                                   shared_ptr<Vectoid::Particles> particles)
        : data_(videoData),
          particles_(particles) {
    Video::Data                        &data      = *data_;
    const int                           randomMax = 10000;
    mt19937                             randomGenerator;
    random::uniform_int_distribution<>  randomDistribution(0, randomMax);
    for (int i = 0; i < data.mapParameters->numStars; i++) {
        float t = (float)randomDistribution(randomGenerator) / (float)randomMax;
        float x = data.mapParameters->starFieldCoordRange.AffineCombination(t);
        data.mapParameters->starFieldCoordRange.Clamp(&x);
        t = (float)randomDistribution(randomGenerator) / (float)randomMax;
        float y = data.mapParameters->starFieldCoordRange.AffineCombination(t);
        data.mapParameters->starFieldCoordRange.Clamp(&y);
        t = (float)randomDistribution(randomGenerator) / (float)randomMax;
        float z = data.mapParameters->starFieldCoordRange.AffineCombination(t);
        data.mapParameters->starFieldCoordRange.Clamp(&z);
        particles_->Add(Vector(x, y, z), Vector());
    }
}

bool StarFieldProcess::Execute(const Process::Context &context) {
    Video::Data &data = *data_;
    Vector       base = data.camera->Position();
    ReusableItems<Particles::ParticleInfo>::Iterator iter = particles_->GetIterator();
    while (Particles::ParticleInfo *particle = iter.Next()) {
        Vector position = particle->position;
        Range xRange(data.mapParameters->starFieldCoordRange, base.x);
        xRange.ClampModulo(&position.x);
        Range yRange(data.mapParameters->starFieldCoordRange, base.y);
        yRange.ClampModulo(&position.y);
        Range zRange(data.mapParameters->starFieldCoordRange, base.z);
        zRange.ClampModulo(&position.z);
        particle->position = position;
        particle->hidden   = (position.y < data.mapParameters->starFieldMinHeight);
    }
    return true;
}

}    // Namespace Zarch.
}    // Namespace kxm.
