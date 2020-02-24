#ifndef KXM_GAME_NETWORKEVENTCOUPLING_H_
#define KXM_GAME_NETWORKEVENTCOUPLING_H_

#include <memory>
#include <thread>

namespace K {
namespace IO {
    class SocketStream;
}
}

namespace kxm {
namespace Game {

class EventLoopHub;

//! Extends the event mechanism to other nodes across the network.
/*!
 *  \ingroup Game
 */
class NetworkEventCoupling {
  public:
    NetworkEventCoupling(const std::shared_ptr<K::IO::SocketStream> &stream,
                         const std::shared_ptr<kxm::Game::EventLoopHub> &hub);
    ~NetworkEventCoupling();

  private:
    class SharedState;
    class Reader;
    class Writer;

    std::shared_ptr<SharedState> sharedState_;
    std::shared_ptr<Reader>      reader_;
    std::shared_ptr<Writer>      writer_;

    std::shared_ptr<std::thread> readerThread_;
    std::shared_ptr<std::thread> writerThread_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLING_H_
