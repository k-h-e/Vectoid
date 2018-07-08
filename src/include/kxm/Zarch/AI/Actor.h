#ifndef KXM_ZARCH_AI_ACTOR_H_
#define KXM_ZARCH_AI_ACTOR_H_

#include <memory>
#include <kxm/Core/ActionInterface.h>
#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;

namespace AI {

class Data;

//! Base class to actors inside the AI subsystem.
/*!
 *  \ingroup ZarchAI
 */
class Actor : public EventHandlerCore, public virtual Core::ActionInterface {
  public:
    Actor(const std::shared_ptr<Data> &data);
    // Default copy and move ok.
    void Reset(const ActorCreationEvent &event);
  
  protected:
    Game::ActorName       name_;
    std::shared_ptr<Data> data_;
};

}    // Namespace AI.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_AI_ACTOR_H_
