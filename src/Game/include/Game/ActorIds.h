#ifndef KXM_GAME_ACTORIDS_
#define KXM_GAME_ACTORIDS_

#include <vector>

namespace kxm {
namespace Game {

class ActorId;

//! Keeps track of valid actor ids.
/*!
 *  \ingroup Game
 */
class ActorIds {
  public:
    ActorIds(const ActorIds &other)            = delete;
    ActorIds &operator=(const ActorIds &other) = delete;
    ActorIds(ActorIds &&other)                 = delete;
    ActorIds &operator=(ActorIds &&other)      = delete;
    //! Tells the object that the specified actor id is now valid.
    void Register(const ActorId &id);
    //! Tells the object that the specified actor id is no longer valid.
    void Unregister(const ActorId &id);
    //! Tells whether or not the specified id is valid.
    bool Valid(const ActorId &id);
    
  private:
    std::vector<uint32_t> incarnations_;
};

}    // NamespaceGame.
}    // Namespace kxm.

#endif    // KXM_GAME_ACTORIDS_
