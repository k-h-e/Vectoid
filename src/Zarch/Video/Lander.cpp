#include <Zarch/Video/Lander.h>

#include <Vectoid/Camera.h>
#include <Vectoid/CoordSys.h>
#include <Vectoid/Geode.h>
#include <Vectoid/Particles.h>
#include <Vectoid/AgeColoredParticles.h>
#include <Zarch/LanderGeometry.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Events/MoveEvent.h>
#include <Zarch/Events/VelocityEvent.h>
#include <Zarch/Events/ThrusterEvent.h>
#include <Zarch/Video/Data.h>
#include <Zarch/Video/TerrainRenderer.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

Lander::Lander()
        : thrusterParticles_(new Particles()) {
    coordSys_ = make_shared<CoordSys>();
    coordSys_->AddChild(make_shared<Geode>(make_shared<LanderGeometry>()));
    
    thrusterParticlesGeode_ = make_shared<Geode>(make_shared<AgeColoredParticles>(thrusterParticles_));
              
    Reset(false, std::shared_ptr<Data>());
}

void Lander::Reset(bool hasFocus, const std::shared_ptr<Data> &data) {
    if (data.get() != data_.get()) {    // Performance optimization.
        data_ = data;
    }
    thrusterActive_        = false;
    particleTimeCarryOver_ = 0.0f;
    hasFocus_              = hasFocus;
}

void Lander::AttachToCamera(const shared_ptr<Camera> &camera) {
    camera->AddChild(coordSys_);
    camera->AddChild(thrusterParticlesGeode_);
}

void Lander::Handle(const MoveEvent &event) {
    coordSys_->SetTransform(event.transform);
    if (hasFocus_) {
        Vector position;
        event.transform.GetTranslationPart(&position);
            
        Vector cameraPosition = position;
        if (cameraPosition.y < data_->mapParameters->cameraMinHeight) {
            cameraPosition.y = data_->mapParameters->cameraMinHeight;
        }
        data_->camera->SetPosition(Vector(cameraPosition.x, cameraPosition.y, cameraPosition.z + 5.0f));

        data_->terrainRenderer->SetObserverPosition(position.x, position.z);
    }
}

void Lander::Handle(const VelocityEvent &event) {
    velocity_ = event.velocity;
}

void Lander::Handle(const ThrusterEvent &event) {
    thrusterActive_ = event.thrusterActive;
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
