#ifndef KXM_ZARCH_GAMELOGIC_DATA_H_
#define KXM_ZARCH_GAMELOGIC_DATA_H_

#include <vector>
#include <Game/ActorNaming.h>
#include <Zarch/Events/ActorCreationEvent.h>
#include <Zarch/Events/ActorTerminationEvent.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class MapParameters;

namespace GameLogic {

struct Data {
    Data() : deltaTimeS(0.0f) {}
    Game::ActorNaming                                              actorNaming;
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop;
    float                                                          deltaTimeS;
    std::vector<ActorCreationEvent>                                actorCreationEvents;
    std::vector<Game::ActorName>                                   actorsToTerminate;
    std::shared_ptr<MapParameters>                                 mapParameters;
};

}    // Namespace Physics
}    // Namespace Zarch
}    // Namespace kxm

#endif    // KXM_ZARCH_GAMELOGIC_DATA_H_
