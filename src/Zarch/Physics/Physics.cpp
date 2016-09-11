#include <Zarch/Physics/Physics.h>

#include <kxm/Core/logging.h>
#include <Game/EventLoop.h>
#include <Zarch/Physics/Lander.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Terrain.h>
#include <Zarch/ControlsState.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Events/UpdatePhysicsEvent.h>
#include <Zarch/Events/ActorCreatedEvent.h>
#include <Zarch/Events/PhysicsUpdatedEvent.h>
#include <Zarch/Events/ControlsEvent.h>

using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace Physics {

Physics::Physics(shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> eventLoop)
        : actions_(new Actions()),
          landers_(actions_),
          lastUpdateTime_(steady_clock::now()) {
    data_ = shared_ptr<Data>(new Data());
    data_->mapParameters = shared_ptr<MapParameters>(new MapParameters());
    data_->terrain       = shared_ptr<Terrain>(new Terrain(data_->mapParameters));
    data_->eventLoop     = eventLoop;
    
    data_->eventLoop->RegisterHandler(UpdatePhysicsEvent::type, this);
    data_->eventLoop->RegisterHandler(ActorCreatedEvent::type, this);
    data_->eventLoop->RegisterHandler(ControlsEvent::type, this);
}

Physics::~Physics() {
    // Nop.
}

void Physics::Handle(const UpdatePhysicsEvent &event) {
    auto now = steady_clock::now();
    int milliSeconds = (int)duration_cast<milliseconds>(now - lastUpdateTime_).count();
    lastUpdateTime_ = now;
    data_->updateDeltaTimeS = (float)milliSeconds / 1000.0f;
    
    actions_->Execute();
    data_->eventLoop->Post(PhysicsUpdatedEvent());
}

void Physics::Handle(const ActorCreatedEvent &event) {
    int              storageId;
    EventHandlerCore *newActor = nullptr;
    switch (event.actorType) {
        case LanderActor:
            newActor = landers_.Get(&storageId);
            static_cast<Lander *>(newActor)->Reset(event.actor, data_);
            break;
        
        default:
            break;
    }
    
    if (newActor) {
        actorMap_.Register(event.actor, ActorInfo(event.actorType, storageId, newActor));
    }
}

void Physics::Handle(const ControlsEvent &event) {
    ActorInfo *info = actorMap_.Get(event.actor);
    if (info) {
        info->actor()->Handle(event);
    }
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
