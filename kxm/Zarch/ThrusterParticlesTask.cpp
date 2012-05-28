//
//  ThrusterParticlesTask.cpp
//  kxm
//
//  Created by Kai Hergenroether on 5/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/ThrusterParticlesTask.h>

#include <kxm/Vectoid/Vector.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Zarch/MapParameters.h>


using boost::shared_ptr;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

ThrusterParticlesTask::ThrusterParticlesTask(
    shared_ptr<Particles> particles, shared_ptr<const LanderTask::LanderStateInfo> landerState,
    shared_ptr<const Game::FrameTimeTask::FrameTimeInfo> timeInfo,
    shared_ptr<const MapParameters> mapParameters)
        : particles_(particles),
          landerState_(landerState),
          timeInfo_(timeInfo),
          mapParameters_(mapParameters),
          particleTimeCarryOver_(0.0f) {
}

void ThrusterParticlesTask::Execute() {
    // Move and age particles...
    float  time               = timeInfo_->timeSinceLastFrame;
    Vector landerPosition     = landerState_->transform.TranslationPart(),
           lastLanderPosition = landerPosition - time*landerState_->velocity; 
    Particles::Iterator iter = particles_->BeginIteration();
    Particles::ParticleInfo *particle;
    particlesToDiscard_.clear();
    while ((particle = iter.Next())) {
        particle->velocity.y += time * -mapParameters_->gravity;
        particle->position   += time * particle->velocity;
        mapParameters_->xRange.ClampModulo(&particle->position.x);
        mapParameters_->xRange.ExpandModuloForObserver(landerPosition.x, &particle->position.x); 
        mapParameters_->zRange.ClampModulo(&particle->position.z);
        mapParameters_->zRange.ExpandModuloForObserver(landerPosition.z, &particle->position.z);
        particle->age        += timeInfo_->timeSinceLastFrame;
        if (particle->age >= mapParameters_->maxThrusterParticleAge)
            particlesToDiscard_.push_back(iter.CurrentId());
    }
    // Discard those particles that are too old...
    if ((int)particlesToDiscard_.size() != 0)
        particles_->RemoveParticles(particlesToDiscard_); 
    
    // Add new particles...?
    if (landerState_->thrusterEnabled && (time > 0.0f)) {
        Transform transform(landerState_->transform);
        transform.SetTranslationPart(Vector());
        float timeLeft = time - particleTimeCarryOver_;
        while (timeLeft > 0.0f) {
            Particles::ParticleInfo *particle = particles_->AddParticle(Vector(), Vector());
            Vector ejectDirection(mapParameters_->thrusterParticleSpread * particle->random0,
                                  -1.0f,
                                  mapParameters_->thrusterParticleSpread * particle->random1),
                   ejectDisplacement(particle->random0, 0.0f, particle->random1);
            transform.ApplyTo(&ejectDirection);
            transform.ApplyTo(&ejectDisplacement);
            particle->velocity =   landerState_->velocity
                                 + mapParameters_->thrusterExhaustVelocity*ejectDirection;
            
            float t = 1.0f - timeLeft/time;
            particle->position =   (1.0f - t)*lastLanderPosition + t*landerPosition
                                 + mapParameters_->thrusterJetSize*ejectDisplacement
                                 + timeLeft*particle->velocity;
            timeLeft -= mapParameters_->thrusterExhaustInterval;
        }
        particleTimeCarryOver_ = -timeLeft;
    }
}

}    // Namespace Zarch.
}    // Namespace kxm.
