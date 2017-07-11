#include <kxm/Zarch/Video/Saucer.h>

#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Zarch/SaucerGeometry.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Video/Data.h>
#include <kxm/Zarch/Video/TerrainRenderer.h>

using namespace std;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

Saucer::Saucer() {
    coordSys_ = make_shared<CoordSys>();
    coordSys_->AddChild(make_shared<Geode>(make_shared<SaucerGeometry>()));
}

void Saucer::GetTransform(Vectoid::Transform *outTransform) {
    coordSys_->GetTransform(outTransform);
    outTransform->SetTranslationPart(position_);    // Our CoordSys's position gets observer-corrected!
}
    
void Saucer::GetVelocity(Vectoid::Vector *outVelocity) {
    *outVelocity = Vector();
}

void Saucer::Handle(const ActorCreationEvent &event) {
    event.initialTransform.GetTranslationPart(&position_);
    coordSys_->SetTransform(event.initialTransform);
    data_->camera->AddChild(coordSys_);
}

void Saucer::Handle(const ActorTerminationEvent &event) {
    data_->camera->RemoveChild(coordSys_);
    
    // Add explosion particles...
    Vector position;
    coordSys_->GetPosition(&position);
    for (int i = 0; i < 100; ++i) {
        Particles::ParticleInfo *particle      = &data_->thrusterParticles->Add(Vector(), Vector()),
                                *otherParticle = &data_->thrusterParticles->Add(Vector(), Vector());
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

void Saucer::Handle(const MoveEvent &event) {
    event.transform.GetTranslationPart(&position_);
    coordSys_->SetTransform(event.transform);
}

void Saucer::ExecuteAction() {
    Vector landerPosition;
    data_->terrainRenderer->GetObserverPosition(&landerPosition);
    Vector position;
    coordSys_->GetPosition(&position);
    data_->mapParameters->CorrectForObserver(&position, landerPosition);
    coordSys_->SetPosition(position);
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
