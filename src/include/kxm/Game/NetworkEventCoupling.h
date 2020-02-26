#ifndef KXM_GAME_NETWORKEVENTCOUPLING_H_
#define KXM_GAME_NETWORKEVENTCOUPLING_H_

#include <memory>
#include <thread>
#include <K/Core/CompletionNotifierInterface.h>

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
class NetworkEventCoupling : public virtual K::Core::CompletionNotifierInterface {
  public:
    NetworkEventCoupling(const std::shared_ptr<K::IO::SocketStream> &stream,
                         const std::shared_ptr<kxm::Game::EventLoopHub> &hub);
    ~NetworkEventCoupling();
    virtual void RegisterCompletionHandler(K::Core::CompletionHandlerInterface &handler, int operationId);
    virtual void UnregisterCompletionHandler(K::Core::CompletionHandlerInterface &handler);

  private:
    class SharedState;
    class Reader;
    class Writer;

    std::shared_ptr<SharedState>         sharedState_;
    std::shared_ptr<K::IO::SocketStream> stream_;
    std::shared_ptr<Reader>              reader_;
    std::shared_ptr<Writer>              writer_;

    std::shared_ptr<std::thread> readerThread_;
    std::shared_ptr<std::thread> writerThread_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLING_H_
