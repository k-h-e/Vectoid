#ifndef KXM_ZARCH_ACTORINFO_
#define KXM_ZARCH_ACTORINFO_

#include <Zarch/ActorType.h>

namespace kxm {
namespace Zarch {

class EventHandlerCore;

//! To be used with <c>Game::ActorMap</c>.
class ActorInfo {
  public:
    ActorInfo() : type_(LanderActor), storageId_(0), actor_(nullptr) {}
    ActorInfo(ActorType type, int storageId, EventHandlerCore *actor)
        : type_(type),
          storageId_(storageId),
          actor_(actor) {}
        // Default copy/move okay.
    ActorType type()          { return type_; }
    int storageId()           { return storageId_; }
    EventHandlerCore *actor() { return actor_; }
  
  private:
    ActorType        type_;
    int              storageId_;
    EventHandlerCore *actor_;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_ACTORINFO_

