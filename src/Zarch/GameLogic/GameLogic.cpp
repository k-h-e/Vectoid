//
//  GameLogic.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#include <Zarch/GameLogic/GameLogic.h>

#include <kxm/Core/logging.h>
#include <Game/EventQueue.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/Events/ControlsStateEvent.h>


using namespace std;
using namespace kxm::Core;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

GameLogic::GameLogic(shared_ptr<EventQueueSchedulingInterface> eventQueue,
                     shared_ptr<Processes<ZarchProcess::ProcessType>> processes)
        : eventQueue_(eventQueue),
          processes_(processes),
          landerThrusterEnabled_(false),
          landerFiringEnabled_(false) {
    // Nop.
}

GameLogic::~GameLogic() {
    // Nop.
}

vector<Event::EventType> GameLogic::EnumerateHandledEvents() {
    return vector<Event::EventType>{ ControlsStateEvent::type };
}

void GameLogic::HandleEvent(const Game::Event &event) {
    static_cast<const ZarchEvent &>(event).DispatchToGameLogic(this);
}

void GameLogic::HandleControlsStateEvent(const ControlsStateEvent &event) {
    // Nop.
}

}    // Namespace Zarch.
}    // Namespace kxm.

