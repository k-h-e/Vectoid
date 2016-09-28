/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchPhysics Physics
 */

#ifndef KXM_ZARCH_PHYSICS_PHYSICS_H_
#define KXM_ZARCH_PHYSICS_PHYSICS_H_

#include <memory>
#include <chrono>

#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Game/ActorMap.h>
#include <kxm/Game/Actions.h>
#include <kxm/Game/ReusableActors.h>
#include <kxm/Zarch/ActorInfo.h>
#include <kxm/Zarch/Events/ZarchEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class ActorCreationEvent;
class ActorTerminationEvent;
class UpdatePhysicsEvent;
class PhysicsOverrideEvent;
class AccelerationEvent;

namespace Physics {

class Data;
class Actor;
class Lander;
class Shot;
class Saucer;

//! Physics subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup ZarchPhysics
 */
class Physics : public EventHandlerCore {
  public:
    Physics(std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop, bool emitTimeEvents);
    ~Physics();
    void Handle(const ActorCreationEvent &event);
    void Handle(const ActorTerminationEvent &event);
    void Handle(const UpdatePhysicsEvent &event);
    void Handle(const PhysicsOverrideEvent &event);
    void Handle(const AccelerationEvent &event);
    
  private:
    Physics(const Physics &other);
    Physics &operator=(const Physics &other);

    std::shared_ptr<Data>                              data_;
    Game::ActorMap<ActorInfo<Actor>>                   actorMap_;
    std::shared_ptr<Game::Actions>                     actions_;
    Game::ReusableActors<Lander>                       landers_;
    Game::ReusableActors<Shot>                         shots_;
    Game::ReusableActors<Saucer>                       saucers_;
    std::chrono::time_point<std::chrono::steady_clock> lastUpdateTime_;
    bool                                               emitTimeEvents_;
};

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICS_PHYSICS_H_
