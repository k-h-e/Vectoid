//
//  GameLogic.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#include <kxm/Zarch/GameLogic/GameLogic.h>
#include <kxm/Zarch/events.h>


using namespace kxm::Game;


namespace kxm {
namespace Zarch {

GameLogic::GameLogic()
        : landerThrusterEnabled_(false),
          landerFiringEnabled_(false) {
}

void GameLogic::HandleEvent(const Game::Event &event) {
    switch (static_cast<const ZarchEvent &>(event).Type()) {
        case ZarchEvent::ControlsStateEvent:
            break;
            
        default:
            break;
    }
}

}    // Namespace Zarch.
}    // Namespace kxm.

