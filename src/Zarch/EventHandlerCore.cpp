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

void EventHandlerCore::Handle(const MoveEvent &event) {
    Log(this).Stream() << "Unhandled MoveEvent!" << endl;
}

void EventHandlerCore::Handle(const VelocityEvent &event) {
    Log(this).Stream() << "Unhandled VelocityEvent!" << endl;
}

void EventHandlerCore::Handle(const ThrusterEvent &event) {
    Log(this).Stream() << "Unhandled ThrusterEvent!" << endl;
}

void EventHandlerCore::Handle(const ShotFiredEvent &event) {
    Log(this).Stream() << "Unhandled ShotFiredEvent!" << endl;
}

void EventHandlerCore::Handle(const ControlsEvent &event) {
    Log(this).Stream() << "Unhandled ControlsEvent!" << endl;
}

void EventHandlerCore::Handle(const FrameGeneratedEvent &event) {
    Log(this).Stream() << "Unhandled FrameGeneratedEvent!" << endl;
}

void EventHandlerCore::Handle(const UpdatePhysicsEvent &event) {
    Log(this).Stream() << "Unhandled UpdatePhysicsEvent!" << endl;
}

void EventHandlerCore::Handle(const PhysicsUpdatedEvent &event) {
    Log(this).Stream() << "Unhandled PhysicsUpdatedEvent!" << endl;
}

}    // Namespace Zarch.
}    // Namespace kxm.
