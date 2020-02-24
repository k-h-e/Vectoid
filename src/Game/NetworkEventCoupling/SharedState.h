#ifndef KXM_GAME_NETWORKEVENTCOUPLING_SHAREDSTATE_H_
#define KXM_GAME_NETWORKEVENTCOUPLING_SHAREDSTATE_H_

#include <mutex>
#include <kxm/Game/NetworkEventCoupling.h>

namespace kxm {
namespace Game {

//! State shared between threads of the network event coupling.
/*!
 *  \ingroup Game
 *
 *  The class is thread-safe (i.e. all public methods).
 */
class NetworkEventCoupling::SharedState {
  public:

  private:
    std::mutex lock_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLING_SHAREDSTATE_H_
