#ifndef KXM_GAME_ACTORNAMING_
#define KXM_GAME_ACTORNAMING_

#include <Game/ActorName.h>

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
    
    //! Creates and hands out a new actor name.
    ActorName Get();
    //! Tells the naming authority that the specified name is no longer needed.
    void Put(const ActorName &name);
    
  private:
    std::vector<uint32_t>   incarnations_;
    std::unordered_set<int> freeIds_;
};

}    // NamespaceGame.
}    // Namespace kxm.

#endif    // KXM_GAME_ACTORNAMING_
