#ifndef KXM_ZARCH_ACTORINFO_H_
#define KXM_ZARCH_ACTORINFO_H_

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
    ActorType Type()    { return type_; }
    int StorageId()     { return storageId_; }
    ActorClass *Actor() { return actor_; }
  
  private:
    ActorType  type_;
    int        storageId_;
    ActorClass *actor_;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_ACTORINFO_H_

