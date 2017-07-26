#ifndef KXM_ZARCH_GAMELOGIC_DATA_H_
#define KXM_ZARCH_GAMELOGIC_DATA_H_

#include <vector>
#include <kxm/Game/ActorNaming.h>
#include <kxm/Zarch/ActorInfo.h>
#include <kxm/Game/ActorMap.h>
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
    Game::ActorNaming                                              actorNaming;
    Game::ActorMap<ActorInfo<Actor>>                               actorMap;
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop;
    float                                                          deltaTimeS,
                                                                   landerRespawnTimeS;
    std::vector<ActorCreationEvent>                                actorCreationEvents;
    std::vector<Game::ActorName>                                   actorsToTerminate;
    std::shared_ptr<MapParameters>                                 mapParameters;
    std::shared_ptr<Terrain>                                       terrain;
    
    Data() : deltaTimeS(0.0f), landerRespawnTimeS(0.0f) {}
    void ScheduleActorCreation(const ActorCreationEvent &event) {
        actorCreationEvents.push_back(event);
    }
    void ScheduleActorForTermination(const Game::ActorName &name) {
        actorsToTerminate.push_back(name);
    }
};

}    // Namespace Physics
}    // Namespace Zarch
}    // Namespace kxm

#endif    // KXM_ZARCH_GAMELOGIC_DATA_H_
