#ifndef ZARCH_PHYSICS_LANDER_H_
#define ZARCH_PHYSICS_LANDER_H_

#include <memory>
#include <kxm/Core/ActionInterface.h>
#include <Game/ActorName.h>
#include <Vectoid/Vector.h>
#include <Vectoid/Transform.h>
#include <Zarch/ControlsState.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {
namespace Physics {

class Data;

//! Represents a lander inside the physics sub system.
/*!
 *  \ingroup ZarchPhysics
 */
class Lander : public EventHandlerCore, public virtual Core::ActionInterface {
  public:
    Lander();
    Lander(const Lander &other)            = delete;
    Lander &operator=(const Lander &other) = delete;
    Lander(Lander &&other)                 = delete;
    Lander &operator=(Lander &&other)      = delete;
    void Reset(const Game::ActorName &name, const std::shared_ptr<Data> &data);
    void ExecuteAction();
    void Handle(const ControlsEvent &event);
    
  private:
    Game::ActorName       name_;
    Vectoid::Transform    transform_;
    Vectoid::Vector       heading_,
                          velocity_;
    ControlsState         controls_;
    bool                  oldThrusterActive_;
    float                 shotsParticleTimeCarryOver_;
    std::shared_ptr<Data> data_;       // Null after default construction!
};

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // ZARCH_PHYSICS_LANDER_H_
