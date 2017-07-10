#ifndef KXM_ZARCH_GAMELOGIC_SHOT_H_
#define KXM_ZARCH_GAMELOGIC_SHOT_H_

#include <memory>
#include <kxm/Zarch/GameLogic/Actor.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;
class CollisionEvent;

namespace GameLogic {

class Data;

//! Represents a shot inside the game logic.
/*!
 *  \ingroup ZarchGameLogic
 */
class Shot : public Actor {
  public:
    Shot();
    Shot(const Shot &other)            = delete;
    Shot &operator=(const Shot &other) = delete;
    Shot(Shot &&other)                 = delete;
    Shot &operator=(Shot &&other)      = delete;
    void Handle(const ActorCreationEvent &event);
    void Handle(const CollisionEvent &event);
    void ExecuteAction();
    
  private:
    float ageS_;
};

}    // Namespace GameLogic.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_GAMELOGIC_SHOT_H_
