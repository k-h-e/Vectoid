#ifndef KXM_ZARCH_AI_SAUCER_H_
#define KXM_ZARCH_AI_SAUCER_H_

#include <kxm/Zarch/AI/Actor.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;

namespace AI {

class Data;

//! Represents an enemy saucer inside the AI subsystem.
/*!
 *  \ingroup ZarchAI
 */
class Saucer : public Actor {
  public:
    Saucer();
    Saucer(const Saucer &other)            = delete;
    Saucer &operator=(const Saucer &other) = delete;
    Saucer(Saucer &&other)                 = delete;
    Saucer &operator=(Saucer &&other)      = delete;
    void Handle(const ActorCreationEvent &event);
    void ExecuteAction();
  
  private:
};

}    // Namespace AI.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_AI_SAUCER_H_
