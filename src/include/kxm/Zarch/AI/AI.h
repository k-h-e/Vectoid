/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchAI AI
 * \brief Zarch's AI subsystem.
 */

#ifndef KXM_ZARCH_AI_AI_H_
#define KXM_ZARCH_AI_AI_H_

#include <memory>
#include <kxm/Game/ActorMap.h>
#include <kxm/Game/ReusableActors.h>
#include <kxm/Zarch/ActorInfo.h>
#include <kxm/Zarch/Events/TriggerEvent.h>
#include <kxm/Zarch/EventHandlerCore.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class ActorCreationEvent;
class ActorTerminationEvent;
class MoveEvent;
class TriggerEvent;

namespace AI {

class Data;
class Actor;
class Saucer;

//! AI subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup ZarchAI
 */
class AI : public EventHandlerCore {
  public:
    AI(const std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> &eventLoop,
       TriggerEvent::Trigger anInTrigger, TriggerEvent::Trigger anOutTrigger);
    AI(const AI &other)            = delete;
    AI &operator=(const AI &other) = delete;
    AI(AI &&other)                 = delete;
    AI &operator=(AI &&other)      = delete;
    ~AI();
    void Handle(const ActorCreationEvent &event);
    void Handle(const ActorTerminationEvent &event);
    void Handle(const MoveEvent &event);
    void Handle(const TriggerEvent &event);
    
  private:
    Game::ActorMap<ActorInfo<Actor>> actorMap_;
    std::shared_ptr<Game::Actions>   actions_;
    Game::ReusableActors<Saucer>     saucers_;
    std::shared_ptr<Data>            data_;
    TriggerEvent::Trigger            inTrigger_,
                                     outTrigger_;
};

}    // Namespace AI.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_AI_AI_H_
