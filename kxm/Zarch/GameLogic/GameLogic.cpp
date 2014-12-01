//
//  GameLogic.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#include <kxm/Zarch/GameLogic/GameLogic.h>

#include <kxm/Core/logging.h>
#include <kxm/Zarch/events.h>
#include <kxm/Zarch/Events/ZarchEvent.h>


using namespace std;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

GameLogic::GameLogic()
        : landerThrusterEnabled_(false),
          landerFiringEnabled_(false) {
}

void GameLogic::HandleEvent(const Game::Event &event) {
    static_cast<const ZarchEvent &>(event).DispatchToGameLogic(this);
}

void GameLogic::HandleControlsStateEvent(const ControlsStateEvent &event) {
    // Nop.
}

void GameLogic::HandleEvent(const Game::OldEvent &event) {
    return;
    switch (static_cast<const OldZarchEvent &>(event).Type()) {
        case OldZarchEvent::ControlsStateEvent:
            break;
            
        default:
            break;
    }
}

}    // Namespace Zarch.
}    // Namespace kxm.

