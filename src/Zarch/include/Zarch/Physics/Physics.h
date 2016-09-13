/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchPhysics Physics
 */

#ifndef KXM_ZARCH_PHYSICS_H_
#define KXM_ZARCH_PHYSICS_H_

#include <memory>
#include <chrono>

#include <Vectoid/Transform.h>
#include <Game/ActorName.h>
#include <Game/ActorMap.h>
#include <Game/Actions.h>
#include <Game/ReusableActors.h>
#include <Zarch/ActorInfo.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class ActorCreationEvent;
class ActorTerminationEvent;
class ControlsEvent;

namespace Physics {

class Data;
class Lander;
class Shot;

//! Physics subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup ZarchPhysics
 */
class Physics : public EventHandlerCore {
  public:
    Physics(std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop);
    ~Physics();
    void Handle(const UpdatePhysicsEvent &event);
    void Handle(const ActorCreationEvent &event);
    void Handle(const ActorTerminationEvent &event);
    void Handle(const ControlsEvent &event);
    
  private:
    Physics(const Physics &other);
    Physics &operator=(const Physics &other);

    std::shared_ptr<Data>                              data_;
    Game::ActorMap<ActorInfo>                          actorMap_;
    std::shared_ptr<Game::Actions>                     actions_;
    Game::ReusableActors<Lander>                       landers_;
    Game::ReusableActors<Shot>                         shots_;
    std::chrono::time_point<std::chrono::steady_clock> lastUpdateTime_;
};

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICS_H_
