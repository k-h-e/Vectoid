#ifndef KXM_ZARCH_PHYSICS_SHOT_H_
#define KXM_ZARCH_PHYSICS_SHOT_H_

#include <memory>
#include <kxm/Zarch/Physics/Actor.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;

namespace Physics {

class Data;

//! Represents a shot inside the physics sub system.
/*!
 *  \ingroup ZarchPhysics
 */
class Shot : public Actor {
  public:
    Shot();
    Shot(const Shot &other)            = delete;
    Shot &operator=(const Shot &other) = delete;
    Shot(Shot &&other)                 = delete;
    Shot &operator=(Shot &&other)      = delete;
    void Handle(const ActorCreationEvent &event);
    void ExecuteAction();
};

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICS_SHOT_H_
