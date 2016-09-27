#include <kxm/Zarch/Video/Saucer.h>

#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Zarch/SaucerGeometry.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Video/Data.h>

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
}
    
void Saucer::GetVelocity(Vectoid::Vector *outVelocity) {
    *outVelocity = Vector();
}

void Saucer::Handle(const ActorCreationEvent &event) {
    coordSys_->SetTransform(event.initialTransform);
    data_->camera->AddChild(coordSys_);
}

void Saucer::Handle(const ActorTerminationEvent &event) {
    data_->camera->RemoveChild(coordSys_);
}

void Saucer::Handle(const MoveEvent &event) {
    coordSys_->SetTransform(event.transform);
}

void Saucer::ExecuteAction() {
    // Nop.
}

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.
