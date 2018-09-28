#include <kxm/Zarch/Video/Lander.h>

#include <kxm/Vectoid/PerspectiveProjection.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Vectoid/AgeColoredParticles.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/SimpleGeometry.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/ControlsEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Events/VelocityEvent.h>
#include <kxm/Zarch/Video/Data.h>
#include <kxm/Zarch/Video/RenderTargetInterface.h>
#include <kxm/Zarch/Video/SimpleGeometryRenderer.h>
#include <kxm/Zarch/Video/TerrainRenderer.h>

using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

Lander::Lander(const std::shared_ptr<Data> &data)
        : Actor(data) {
    shared_ptr<SimpleGeometry> landerGeometry = SimpleGeometry::NewLanderGeometry();
    
    coordSys_ = data_->renderTarget->NewCoordSys();
    coordSys_->AddChild(data_->renderTarget->NewGeode(data_->renderTarget->NewSimpleGeometryRenderer(landerGeometry)));
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
    data_->camera->AddChild(coordSys_);
}

void Lander::Handle(const ActorTerminationEvent &event) {
    if (hasFocus_) {
        data_->focusLander = ActorName();
    }
    
    Vector position;
    coordSys_->GetPosition(&position);
    data_->StartParticleExplosion(position, 300);    
    data_->camera->RemoveChild(coordSys_);
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
        data_->terrainRenderer->SetObserverPosition(position);
        
        if (position.y < data_->mapParameters->cameraMinHeight) {
            position.y = data_->mapParameters->cameraMinHeight;
        }
        position.z += 5.0f;
        data_->camera->SetPosition(position);
        
        data_->statsConsoleCoordSys->SetPosition(position + data_->statsConsolePosition);
    }
}

void Lander::Handle(const VelocityEvent &event) {
    velocity_ = event.velocity;
}

void Lander::ExecuteAction() {
    Data   &data = *data_;
    Vector landerPosition = coordSys_->Position();
    
    // Add new particles...?
    if (thrusterActive_ && (data.frameDeltaTimeS > 0.0f)) {
        Transform transform;
        coordSys_->GetTransform(&transform);
        transform.SetTranslationPart(Vector());
        float timeLeft = data.frameDeltaTimeS - particleTimeCarryOver_;
        while (timeLeft > 0.0f) {
            Particles::ParticleInfo &particle = data_->thrusterParticles->Add(Vector(), Vector());
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
