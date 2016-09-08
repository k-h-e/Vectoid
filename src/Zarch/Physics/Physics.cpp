//
//  NewPhysics.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//

#include <Zarch/Physics/Physics.h>

#include <kxm/Core/logging.h>
#include <Game/EventLoop.h>
#include <Zarch/Physics/LanderProcess.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Terrain.h>
#include <Zarch/ControlsState.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Events/UpdatePhysicsEvent.h>
#include <Zarch/Events/ActorCreatedEvent.h>
#include <Zarch/Events/PhysicsUpdatedEvent.h>
#include <Zarch/Events/ControlsStateEvent.h>

using namespace std;
using namespace std::chrono;
using namespace kxm::Core;
using namespace kxm::Game;

namespace kxm {
namespace Zarch {
namespace Physics {

Physics::Physics(shared_ptr<EventLoop<ZarchEvent, EventHandlerCore>> eventLoop)
        : eventLoop_(eventLoop),
          lastUpdateTime_(steady_clock::now()) {
    data_ = shared_ptr<Data>(new Data());
    data_->mapParameters = shared_ptr<MapParameters>(new MapParameters());
    data_->terrain       = shared_ptr<Terrain>(new Terrain(data_->mapParameters));
    data_->eventLoop     = eventLoop;
    
    eventLoop_->RegisterHandler(UpdatePhysicsEvent::type, this);
    eventLoop_->RegisterHandler(ActorCreatedEvent::type, this);
    eventLoop_->RegisterHandler(ControlsStateEvent::type, this);
    
    landerProcess_ = unique_ptr<LanderProcess>(new LanderProcess(data_));
}

Physics::~Physics() {
    // Nop.
}

void Physics::HandleProcessFinished(ProcessInterface *process) {
    // Nop.
}

void Physics::Handle(const UpdatePhysicsEvent &event) {
    auto now = steady_clock::now();
    int milliSeconds = (int)duration_cast<milliseconds>(now - lastUpdateTime_).count();
    lastUpdateTime_ = now;
    data_->updateDeltaTimeS = (float)milliSeconds / 1000.0f;
    
    landerProcess_->Execute();
    eventLoop_->Post(PhysicsUpdatedEvent());
}

void Physics::Handle(const ActorCreatedEvent &event) {
    switch (event.actorType) {
        case LanderActor:
            assert(data_->landerActor.IsNone());
            data_->landerActor = event.actor;
            break;
        
        default:
            break;
    }
}

void Physics::Handle(const ControlsStateEvent &event) {
    data_->controlsState = event.controlsState;
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
