#include <Zarch/EventHandlerCore.h>

#include <iostream>
#include <kxm/Core/logging.h>

using namespace std;
using namespace kxm::Core;


namespace kxm {
namespace Zarch {

void EventHandlerCore::Handle(const InitializationEvent &event) {
    Log(this).Stream() << "Unhandled InitializationEvent!" << endl;
}
    
void EventHandlerCore::Handle(const ActorCreatedEvent &event) {
    Log(this).Stream() << "Unhandled ActorCreatedEvent!" << endl;
}

void EventHandlerCore::Handle(const FrameGeneratedEvent &event) {
    Log(this).Stream() << "Unhandled FrameGeneratedEvent!" << endl;
}
    
void EventHandlerCore::Handle(const FrameTimeEvent &event) {
    Log(this).Stream() << "Unhandled FrameTimeEvent!" << endl;
}

void EventHandlerCore::Handle(const UpdatePhysicsEvent &event) {
    Log(this).Stream() << "Unhandled UpdatePhysicsEvent!" << endl;
}

void EventHandlerCore::Handle(const PhysicsUpdatedEvent &event) {
    Log(this).Stream() << "Unhandled PhysicsUpdatedEvent!" << endl;
}

void EventHandlerCore::Handle(const ControlsStateEvent &event) {
    Log(this).Stream() << "Unhandled ControlsStateEvent!" << endl;
}

void EventHandlerCore::Handle(const LanderMoveEvent &event) {
    Log(this).Stream() << "Unhandled LanderMoveEvent!" << endl;
}

void EventHandlerCore::Handle(const LanderVelocityEvent &event) {
    Log(this).Stream() << "Unhandled LanderVelocityEvent!" << endl;
}

void EventHandlerCore::Handle(const LanderThrusterEvent &event) {
    Log(this).Stream() << "Unhandled LanderThrusterEvent!" << endl;
}

}    // Namespace Zarch.
}    // Namespace kxm.
