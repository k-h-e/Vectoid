#include <kxm/Zarch/Video/Shot.h>

#include <kxm/Vectoid/Particles.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Video/Data.h>

using namespace std;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

Shot::Shot()
        : particleStorageId_(-1) {
    // Nop.
}

void Shot::GetTransform(Vectoid::Transform *outTransform) {
    *outTransform = Transform();
}
    
void Shot::GetVelocity(Vectoid::Vector *outVelocity) {
    *outVelocity = Vector();
}

void Shot::Handle(const ActorCreationEvent &event) {
    Vector initialPosition;
    event.initialTransform.GetTranslationPart(&initialPosition);
    data_->shotParticles->Add(initialPosition, event.initialVelocity, &particleStorageId_);
}

void Shot::Handle(const ActorTerminationEvent &event) {
    data_->shotParticles->Remove(particleStorageId_);
}

void Shot::Handle(const MoveEvent &event) {
    Particles::ParticleInfo &info = data_->shotParticles->Get(particleStorageId_);
    event.transform.GetTranslationPart(&info.position);
}

void Shot::ExecuteAction() {
    // Nop.
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
