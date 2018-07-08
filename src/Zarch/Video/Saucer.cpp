#include <kxm/Zarch/Video/Saucer.h>

#include <kxm/Vectoid/CoordSys.h>
#include <kxm/Vectoid/Camera.h>
#include <kxm/Vectoid/Geode.h>
#include <kxm/Vectoid/Particles.h>
#include <kxm/Zarch/SimpleGeometry.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>
#include <kxm/Zarch/Events/MoveEvent.h>
#include <kxm/Zarch/Video/Data.h>
#include <kxm/Zarch/Video/RenderTargetInterface.h>
#include <kxm/Zarch/Video/SimpleGeometryRenderer.h>
#include <kxm/Zarch/Video/TerrainRenderer.h>

using namespace std;
using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {
namespace Video {

Saucer::Saucer(const std::shared_ptr<Data> &data)
        : Actor(data) {
    shared_ptr<SimpleGeometry> saucerGeometry = SimpleGeometry::NewSaucerGeometry();

    coordSys_ = data_->renderTarget->NewCoordSys();
    coordSys_->AddChild(make_shared<Geode>(data_->renderTarget->NewSimpleGeometryRenderer(saucerGeometry)));
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
    Vector position;
    coordSys_->GetPosition(&position);
    data_->StartParticleExplosion(position, 200);
    data_->camera->RemoveChild(coordSys_);
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
