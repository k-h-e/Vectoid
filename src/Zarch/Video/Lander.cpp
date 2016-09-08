#include <Zarch/Video/Lander.h>

#include <Vectoid/Camera.h>
#include <Vectoid/CoordSys.h>
#include <Vectoid/Geode.h>
#include <Vectoid/Particles.h>
#include <Vectoid/AgeColoredParticles.h>
#include <Zarch/LanderGeometry.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Events/MoveEvent.h>
#include <Zarch/Video/Data.h>
#include <Zarch/Video/TerrainRenderer.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

Lander::Lander(const shared_ptr<Data> &data)
        : data_(data),
          thrusterParticles_(new Particles()),
          particleTimeCarryOver_(0.0f) {
    coordSys_ = shared_ptr<CoordSys>(new CoordSys());
    shared_ptr<LanderGeometry> landerGeometry(new LanderGeometry());
    coordSys_->AddChild(shared_ptr<Geode>(new Geode(landerGeometry)));
    
    thrusterParticlesGeode_ = shared_ptr<Geode>(new Geode(shared_ptr<AgeColoredParticles>(
                                  new AgeColoredParticles(thrusterParticles_))));
}

void Lander::AttachToCamera(const shared_ptr<Camera> &camera) {
    camera->AddChild(coordSys_);
    camera->AddChild(thrusterParticlesGeode_);
}

void Lander::GetPosition(Vectoid::Vector *outPosition) {
    coordSys_->GetPosition(outPosition);
}

void Lander::Handle(const MoveEvent &event) {
    coordSys_->SetTransform(event.transform);
}

void Lander::Execute() {
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
    if (data.landerThrusterEnabled && (data.frameDeltaTimeS > 0.0f)) {
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
}

bool Lander::Finished() {
    return false;
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
