#ifndef KXM_GAME_ACTORNAME_
#define KXM_GAME_ACTORNAME_

#include <cassert>
#include <stdint.h>
#include <climits>

namespace kxm {
namespace Game {

//! Identifies an actor.
/*!
 *  \ingroup Game
 */
class ActorName {
  public:
    //! Creates a "none" actor name.
    ActorName() : id_(INT_MAX), incarnation_(0u) {}
    //! Creates an actor as specified.
    ActorName(int anId, uint32_t anIncarnation) : id_(anId), incarnation_(anIncarnation) {
        assert((anId >= 0) && (anId < INT_MAX));
    }
    int Id() const { return id_; }
    uint32_t Incarnation() const { return incarnation_; }
    //! Tells whether the name is the "none" name.
    bool IsNone() const { return (id_ == INT_MAX); }
    
  private:
    int      id_;
    uint32_t incarnation_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_ACTORNAME_
