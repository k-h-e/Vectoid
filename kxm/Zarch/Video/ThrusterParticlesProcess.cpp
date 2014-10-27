//
//  NewThrusterParticlesProcess.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/30/13.
//
//


#include <kxm/Zarch/Video/ThrusterParticlesProcess.h>

#include <kxm/Core/ReusableItems.h>
#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Zarch/MapParameters.h>


using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

ThrusterParticlesProcess::ThrusterParticlesProcess(shared_ptr<Video::Data> data,
                                                   shared_ptr<Vectoid::Particles> particles)
        : data_(data),
          particles_(particles),
          particleTimeCarryOver_(0.0f) {
}

bool ThrusterParticlesProcess::Execute(const ExecutionContext &context) {
    Video::Data &data = *data_;
    
    // Move and age particles...
    Vector landerPosition = data.landerCoordSys->Position(); 
    ReusableItems<Particles::ParticleInfo>::Iterator iter = particles_->GetIterator();
    Particles::ParticleInfo *particle;
    while ((particle = iter.Next())) {
        particle->velocity.y += data.frameDeltaTimeS * -data.mapParameters->gravity;
        particle->position   += data.frameDeltaTimeS * particle->velocity;
        data.mapParameters->xRange.ClampModulo(&particle->position.x);
        data.mapParameters->xRange.ExpandModuloForObserver(landerPosition.x, &particle->position.x);
        data.mapParameters->zRange.ClampModulo(&particle->position.z);
        data.mapParameters->zRange.ExpandModuloForObserver(landerPosition.z, &particle->position.z);
        particle->age        += data.frameDeltaTimeS;
        if (particle->age >= data.mapParameters->maxThrusterParticleAge)
            particles_->Remove(iter.ItemId());
    }
    
    // Add new particles...?
    if (data.landerThrusterEnabled && (data.frameDeltaTimeS > 0.0f)) {
        Transform transform;
        data.landerCoordSys->GetTransform(&transform);
        transform.SetTranslationPart(Vector());
        float timeLeft = data.frameDeltaTimeS - particleTimeCarryOver_;
        while (timeLeft > 0.0f) {
            Particles::ParticleInfo &particle = particles_->Add(Vector(), Vector());
            Vector ejectDirection(data.mapParameters->thrusterParticleSpread * particle.random0,
                                  -1.0f,
                                  data.mapParameters->thrusterParticleSpread * particle.random1),
                   ejectDisplacement(particle.random0, 0.0f, particle.random1);
            transform.ApplyTo(&ejectDirection);
            transform.ApplyTo(&ejectDisplacement);
            particle.velocity =   data.landerVelocity
                                + data.mapParameters->thrusterExhaustVelocity*ejectDirection;
            
            float t = 1.0f - timeLeft/data.frameDeltaTimeS;
            particle.position =   (1.0f - t)*lastLanderPosition_ + t*landerPosition
                                + data.mapParameters->thrusterJetSize*ejectDisplacement
                                + timeLeft*particle.velocity;
            timeLeft -= data.mapParameters->thrusterExhaustInterval;
        }
        particleTimeCarryOver_ = -timeLeft;
    }
    
    lastLanderPosition_ = landerPosition;
    return true;
}

}    // Namespace Zarch.
}    // Namespace kxm.
