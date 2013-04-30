//
//  StarFieldProcess.cpp
//  kxm
//
//  Created by Kai Hergenroether on 6/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/Video/StarFieldProcess.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <kxm/Vectoid/Particles.h>
#include <kxm/Zarch/MapParameters.h>

using boost::shared_ptr;
using namespace boost::random;
using namespace kxm::Core;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

StarFieldProcess::StarFieldProcess(shared_ptr<Particles> particles,
                                   shared_ptr<const CameraProcess::CameraStateInfo> cameraState,
                                   shared_ptr<const MapParameters> mapParameters)
        : particles_(particles),
          cameraState_(cameraState),
          mapParameters_(mapParameters),
          count_(0) {
    const int                  randomMax = 10000;
    mt19937                    randomGenerator;
    uniform_int_distribution<> randomDistribution(0, randomMax);
    for (int i = 0; i < mapParameters_->numStars; i++) {
        float t = (float)randomDistribution(randomGenerator) / (float)randomMax;
        float x = mapParameters->starFieldCoordRange.AffineCombination(t);
        mapParameters->starFieldCoordRange.Clamp(&x);
        t = (float)randomDistribution(randomGenerator) / (float)randomMax;
        float y = mapParameters->starFieldCoordRange.AffineCombination(t);
        mapParameters->starFieldCoordRange.Clamp(&y);
        t = (float)randomDistribution(randomGenerator) / (float)randomMax;
        float z = mapParameters->starFieldCoordRange.AffineCombination(t);
        mapParameters->starFieldCoordRange.Clamp(&z);
        particles->Add(Vector(x, y, z), Vector());
    }
}

bool StarFieldProcess::Execute(const Process::Context &context) {
    Vector cameraPosition = cameraState_->position;
    ReusableItems<Particles::ParticleInfo>::Iterator iter = particles_->GetIterator();
    while (Particles::ParticleInfo *particle = iter.Next()) {
        Vector position = particle->position;
        Range xRange(mapParameters_->starFieldCoordRange, cameraPosition.x);
        xRange.ClampModulo(&position.x);
        Range yRange(mapParameters_->starFieldCoordRange, cameraPosition.y);
        yRange.ClampModulo(&position.y);
        Range zRange(mapParameters_->starFieldCoordRange, cameraPosition.z);
        zRange.ClampModulo(&position.z);
        particle->position = position;
        particle->hidden   = (position.y < mapParameters_->starFieldMinHeight);
    }
    return true;
}

}    // Namespace Zarch.
}    // Namespace kxm.
