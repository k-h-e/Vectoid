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
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/EventHandlerCore.h>
#include <Zarch/Physics/Data.h>
#include <Zarch/Physics/Lander.h>

namespace kxm {
namespace Zarch {

class ActorCreatedEvent;
class ControlsEvent;

namespace Physics {

//! Physics subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup ZarchPhysics
 */
class Physics : public EventHandlerCore {
  public:
    Physics(std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop);
    ~Physics();
    void Handle(const UpdatePhysicsEvent &event);
    void Handle(const ActorCreatedEvent &event);
    void Handle(const ControlsEvent &event);
    
  private:
    Physics(const Physics &other);
    Physics &operator=(const Physics &other);

    std::shared_ptr<Data>                                          data_;
    Game::ActorMap<EventHandlerCore>                               actorMap_;
    std::shared_ptr<Game::Actions>                                 actions_;
    Game::ReusableActors<Lander>                                   landers_;
    std::chrono::time_point<std::chrono::steady_clock>             lastUpdateTime_;
};

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICS_H_
