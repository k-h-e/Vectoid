#include <Zarch/EventHandlerCore.h>

#include <iostream>
#include <kxm/Core/logging.h>

using namespace std;
using namespace kxm::Core;


namespace kxm {
namespace Zarch {

void EventHandlerCore::HandleFrameGeneratedEvent(const FrameGeneratedEvent &event) {
    Log(this).Stream() << "Unhandled FrameGeneratedEvent!" << endl;
}
    
void EventHandlerCore::HandleFrameTimeEvent(const FrameTimeEvent &event) {
    Log(this).Stream() << "Unhandled FrameTimeEvent!" << endl;
}

void EventHandlerCore::HandleControlsStateEvent(const ControlsStateEvent &event) {
    Log(this).Stream() << "Unhandled ControlsStateEvent!" << endl;
}

void EventHandlerCore::HandleLanderMoveEvent(const LanderMoveEvent &event) {
    Log(this).Stream() << "Unhandled LanderMoveEvent!" << endl;
}

void EventHandlerCore::HandleLanderVelocityEvent(const LanderVelocityEvent &event) {
    Log(this).Stream() << "Unhandled LanderVelocityEvent!" << endl;
}

void EventHandlerCore::HandleLanderThrusterEvent(const LanderThrusterEvent &event) {
    Log(this).Stream() << "Unhandled LanderThrusterEvent!" << endl;
}

}    // Namespace Zarch.
}    // Namespace kxm.
