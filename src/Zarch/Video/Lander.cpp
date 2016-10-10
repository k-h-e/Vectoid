#include <kxm/Zarch/Video/Lander.h>

#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Vectoid/AgeColoredParticles.h>
#include <kxm/Zarch/LanderGeometry.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/ControlsEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Events/VelocityEvent.h>
#include <kxm/Zarch/Video/Data.h>
#include <kxm/Zarch/Video/TerrainRenderer.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

Lander::Lander()
        : thrusterParticles_(new Particles()) {
    coordSys_ = make_shared<CoordSys>();
    coordSys_->AddChild(make_shared<Geode>(make_shared<LanderGeometry>()));
    
    thrusterParticlesGeode_ = make_shared<Geode>(make_shared<AgeColoredParticles>(thrusterParticles_));
}

void Lander::GetTransform(Vectoid::Transform *outTransform) {
    coordSys_->GetTransform(outTransform);
}

void Lander::GetVelocity(Vectoid::Vector *outVelocity) {
    *outVelocity = velocity_;
}

void Lander::Handle(const ActorCreationEvent &event) {
    coordSys_->SetTransform(event.initialTransform);
    velocity_              = event.initialVelocity;
    event.initialTransform.GetTranslationPart(&lastPosition_);
    thrusterActive_        = false;
    particleTimeCarryOver_ = 0.0f;
    hasFocus_              = data_->focusLander.IsNone();
    if (hasFocus_) {
        data_->focusLander = event.actor;
    }
    
    // TODO: Clear thruster particles.

    data_->camera->AddChild(coordSys_);
    data_->camera->AddChild(thrusterParticlesGeode_);
}

void Lander::Handle(const ActorTerminationEvent &event) {
    if (hasFocus_) {
        data_->focusLander = ActorName();
    }
    
    data_->camera->RemoveChild(coordSys_);
    data_->camera->RemoveChild(thrusterParticlesGeode_);
}

void Lander::Handle(const ControlsEvent &event) {
    Control control;
    for (int i = 0; i < event.Count(); ++i) {
        event.GetControl(i, &control);
        if (control.Type() == ThrusterControl) {
            thrusterActive_ = (control.Argument() > .5f);
        }
    }
}

void Lander::Handle(const MoveEvent &event) {
    coordSys_->SetTransform(event.transform);
    if (hasFocus_) {
        Vector position;
        event.transform.GetTranslationPart(&position);
        data_->terrainRenderer->SetObserverPosition(position.x, position.z);
        
        if (position.y < data_->mapParameters->cameraMinHeight) {
            position.y = data_->mapParameters->cameraMinHeight;
        }
        position.z += 5.0f;
        data_->camera->SetPosition(position);
    }
}

void Lander::Handle(const VelocityEvent &event) {
    velocity_ = event.velocity;
}

void Lander::ExecuteAction() {
    Data &data = *data_;
    
    // Move and age particles...
    Vector landerPosition = coordSys_->Position();
    ReusableItems<Particles::ParticleInfo>::Iterator iter = thrusterParticles_->GetIterator();
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
            thrusterParticles_->Remove(iter.ItemId());
    }
    
    // Add new particles...?
    if (thrusterActive_ && (data.frameDeltaTimeS > 0.0f)) {
        Transform transform;
        coordSys_->GetTransform(&transform);
        transform.SetTranslationPart(Vector());
        float timeLeft = data.frameDeltaTimeS - particleTimeCarryOver_;
        while (timeLeft > 0.0f) {
            Particles::ParticleInfo &particle = thrusterParticles_->Add(Vector(), Vector());
            Vector ejectDirection(data.mapParameters->thrusterParticleSpread * particle.random0,
                                  -1.0f,
                                  data.mapParameters->thrusterParticleSpread * particle.random1),
                   ejectDisplacement(particle.random0, 0.0f, particle.random1);
            transform.ApplyTo(&ejectDirection);
            transform.ApplyTo(&ejectDisplacement);
            particle.velocity = velocity_ + data.mapParameters->thrusterExhaustVelocity*ejectDirection;
            
            float t = 1.0f - timeLeft/data.frameDeltaTimeS;
            particle.position =   (1.0f - t)*lastPosition_ + t*landerPosition
                                + data.mapParameters->thrusterJetSize*ejectDisplacement
                                + timeLeft*particle.velocity;
            timeLeft -= data.mapParameters->thrusterExhaustInterval;
        }
        particleTimeCarryOver_ = -timeLeft;
    }
    
    lastPosition_ = landerPosition;
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
