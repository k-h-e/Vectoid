#ifndef KXM_GAME_NETWORKEVENTCOUPLING_WRITER_H_
#define KXM_GAME_NETWORKEVENTCOUPLING_WRITER_H_

#include <kxm/Game/NetworkEventCoupling.h>

namespace K {
namespace IO {
    class SocketStream;
}
}

namespace kxm {
namespace Game {

class EventLoopHub;

//! Writer for the network event coupling.
/*!
 *  \ingroup Game
 */
class NetworkEventCoupling::Writer {
  public:
    Writer(const std::shared_ptr<K::IO::SocketStream> &stream, const std::shared_ptr<kxm::Game::EventLoopHub> &hub,
           int hubClientId, std::shared_ptr<SharedState> sharedState);
    void Run();

  private:
    std::shared_ptr<SharedState>             sharedState_;
    std::shared_ptr<K::IO::SocketStream>     stream_;
    std::shared_ptr<kxm::Game::EventLoopHub> hub_;

    int hubClientId_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLING_WRITER_H_
