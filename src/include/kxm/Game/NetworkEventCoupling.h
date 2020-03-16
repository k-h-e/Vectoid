#ifndef KXM_GAME_NETWORKEVENTCOUPLING_H_
#define KXM_GAME_NETWORKEVENTCOUPLING_H_

#include <memory>
#include <kxm/Core/Interface.h>

namespace K {
namespace Core {
    class CompletionHandlerInterface;
    class ThreadPool;
}
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
class NetworkEventCoupling : public virtual kxm::Core::Interface {
  public:
    //! Well, constructor.
    /*!
     *  \param completionHandler
     *  Optional. If given, it will be called with the completion id as parameter when the network event coupling has
     *  shut down.
     */
    NetworkEventCoupling(const std::shared_ptr<K::IO::SocketStream> &stream,
                         const std::shared_ptr<kxm::Game::EventLoopHub> &hub,
                         const std::shared_ptr<K::Core::CompletionHandlerInterface> &completionHandler,
                         int completionId,
                         const std::shared_ptr<K::Core::ThreadPool> &threadPool);
    ~NetworkEventCoupling();

  private:
    static const int readerCompletionId = 0;
    static const int writerCompletionId = 1;

    class SharedState;
    class Reader;
    class Writer;

    std::shared_ptr<SharedState>         sharedState_;
    std::shared_ptr<K::IO::SocketStream> stream_;
    std::shared_ptr<Reader>              reader_;
    std::shared_ptr<Writer>              writer_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLING_H_
