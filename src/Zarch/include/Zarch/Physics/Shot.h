#ifndef ZARCH_PHYSICS_SHOT_H_
#define ZARCH_PHYSICS_SHOT_H_

#include <memory>
#include <kxm/Core/ActionInterface.h>
#include <Game/ActorName.h>
#include <Vectoid/Vector.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;
class ActorTerminationEvent;

namespace Physics {

class Data;

//! Represents a shot inside the physics sub system.
/*!
 *  \ingroup ZarchPhysics
 */
class Shot : public EventHandlerCore, public virtual Core::ActionInterface {
  public:
    Shot();
    Shot(const Shot &other)            = delete;
    Shot &operator=(const Shot &other) = delete;
    Shot(Shot &&other)                 = delete;
    Shot &operator=(Shot &&other)      = delete;
    void Reset(const std::shared_ptr<Data> &data);
    void Handle(const ActorCreationEvent &event);
    void Handle(const ActorTerminationEvent &event);
    void ExecuteAction();
    
  private:
    Game::ActorName       name_;
    Vectoid::Vector       position_,
                          velocity_;
    float                 age_s_;
    bool                  active_;
    std::shared_ptr<Data> data_;       // Null after default construction!
};

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // ZARCH_PHYSICS_SHOT_H_