#ifndef KXM_GAME_NETWORKEVENTCOUPLING_SHAREDSTATE_H_
#define KXM_GAME_NETWORKEVENTCOUPLING_SHAREDSTATE_H_

#include <kxm/Game/NetworkEventCoupling.h>

namespace K {
namespace IO {
    class SocketStream;
}
}

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
    std::shared_ptr<K::IO::SocketStream> GetStream();

  private:
    std::mutex lock_;
    std::shared_ptr<K::IO::SocketStream> stream_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLING_SHAREDSTATE_H_
