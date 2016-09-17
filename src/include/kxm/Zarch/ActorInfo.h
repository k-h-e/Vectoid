#ifndef KXM_ZARCH_ACTORINFO_
#define KXM_ZARCH_ACTORINFO_

#include <kxm/Zarch/ActorType.h>

namespace kxm {
namespace Zarch {

//! To be used with <c>Game::ActorMap</c>.
template<class ActorClass>
class ActorInfo {
  public:
    ActorInfo() : type_(LanderActor), storageId_(0), actor_(nullptr) {}
    ActorInfo(ActorType type, int storageId, ActorClass *actor)
        : type_(type),
          storageId_(storageId),
          actor_(actor) {}
        // Default copy/move okay.
    ActorType type()    { return type_; }
    int storageId()     { return storageId_; }
    ActorClass *actor() { return actor_; }
  
  private:
    ActorType  type_;
    int        storageId_;
    ActorClass *actor_;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_ACTORINFO_

