//
//  GameLogic.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#include <Zarch/GameLogic/GameLogic.h>

#include <kxm/Core/logging.h>
#include <Zarch/Events/ZarchEvent.h>


using namespace std;
using namespace kxm::Core;
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

}    // Namespace Zarch.
}    // Namespace kxm.

