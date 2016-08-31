#ifndef KXM_GAME_ACTORID_
#define KXM_GAME_ACTORID_

#include <stdint.h>

namespace kxm {
namespace Game {

//! Identifies an actor.
/*!
 *  \ingroup Game
 */
struct ActorId {
    int      id;
    uint32_t incarnation;
    //! Creates an actor as specified.
    ActorId(int anId, uint32_t anIncarnation) : id(anId), incarnation(anIncarnation) {}
        // Default copy and move ok.
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_ACTORID_
