#ifndef KXM_ZARCH_GAMELOGIC_DATA_H_
#define KXM_ZARCH_GAMELOGIC_DATA_H_

#include <vector>
#include <kxm/Game/ActorNaming.h>
#include <kxm/Zarch/Events/ActorCreationEvent.h>
#include <kxm/Zarch/Events/ActorTerminationEvent.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class MapParameters;
class Terrain;

namespace GameLogic {

//! Game logic data.
/*!
 *  \ingroup ZarchGameLogic
 */
struct Data {
    Data() : deltaTimeS(0.0f) {}
    Game::ActorNaming                                              actorNaming;
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop;
    float                                                          deltaTimeS;
    std::vector<ActorCreationEvent>                                actorCreationEvents;
    std::vector<Game::ActorName>                                   actorsToTerminate;
    std::shared_ptr<MapParameters>                                 mapParameters;
    std::shared_ptr<Terrain>                                       terrain;
};

}    // Namespace Physics
}    // Namespace Zarch
}    // Namespace kxm

#endif    // KXM_ZARCH_GAMELOGIC_DATA_H_
