#ifndef KXM_GAME_ACTORNAMING_
#define KXM_GAME_ACTORNAMING_

#include <Game/ActorId.h>

#include <vector>
#include <unordered_set>

namespace kxm {
namespace Game {

//! Central authority for keeping track of and assigning new actor ids.
/*!
 *  \ingroup Game
 */
class ActorNaming {
  public:
    ActorNaming();
    ActorNaming(const ActorNaming &other)            = delete;
    ActorNaming &operator=(const ActorNaming &other) = delete;
    ActorNaming(ActorNaming &&other)                 = delete;
    ActorNaming &operator=(ActorNaming &&other)      = delete;
    
    //! Creates and hands out a new actor id.
    ActorId Get();
    //! Tells the naming authority that the specified id is no longer needed.
    void Put(const ActorId &id);
    
  private:
    std::vector<uint32_t>   incarnations_;
    std::unordered_set<int> freeIds_;
};

}    // NamespaceGame.
}    // Namespace kxm.

#endif    // KXM_GAME_ACTORNAMING_
