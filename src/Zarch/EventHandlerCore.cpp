#include <kxm/Zarch/EventHandlerCore.h>

#include <iostream>
#include <kxm/Core/logging.h>

using namespace std;
using namespace kxm::Core;

namespace kxm {
namespace Zarch {

void EventHandlerCore::Handle(const InitializationEvent &event) {
    Log(this).Stream() << "Unhandled InitializationEvent!" << endl;
}

void EventHandlerCore::Handle(const TimeEvent &event) {
    Log(this).Stream() << "Unhandled TimeEvent!" << endl;
}

void EventHandlerCore::Handle(const ActorCreationEvent &event) {
    Log(this).Stream() << "Unhandled ActorCreationEvent!" << endl;
}

void EventHandlerCore::Handle(const ActorTerminationEvent &event) {
    Log(this).Stream() << "Unhandled ActorTerminationEvent!" << endl;
}

void EventHandlerCore::Handle(const MoveEvent &event) {
    Log(this).Stream() << "Unhandled MoveEvent!" << endl;
}

void EventHandlerCore::Handle(const VelocityEvent &event) {
    Log(this).Stream() << "Unhandled VelocityEvent!" << endl;
}

void EventHandlerCore::Handle(const AccelerationEvent &event) {
    Log(this).Stream() << "Unhandled AccelerationEvent!" << endl;
}

void EventHandlerCore::Handle(const ControlsRequestEvent &event) {
    Log(this).Stream() << "Unhandled ControlsRequestEvent!" << endl;
}

void EventHandlerCore::Handle(const ControlsEvent &event) {
    Log(this).Stream() << "Unhandled ControlsEvent!" << endl;
}

void EventHandlerCore::Handle(const ControlsRejectionEvent &event) {
    Log(this).Stream() << "Unhandled ControlsRejectionEvent!" << endl;
}

void EventHandlerCore::Handle(const FrameGeneratedEvent &event) {
    Log(this).Stream() << "Unhandled FrameGeneratedEvent!" << endl;
}

void EventHandlerCore::Handle(const TriggerEvent &event) {
    Log(this).Stream() << "Unhandled TriggerEvent!" << endl;
}

}    // Namespace Zarch.
}    // Namespace kxm.
