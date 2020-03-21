#ifndef KXM_GAME_NETWORKEVENTCOUPLINGSERVER_H_
#define KXM_GAME_NETWORKEVENTCOUPLINGSERVER_H_

#include <memory>

namespace K {
namespace Core {
    class ThreadPool;

}
namespace IO {
    class ListenSocket;
}
}

namespace kxm {
namespace Game {

class EventLoopHub;

//! Installs network event couplings for incoming network connections.
/*!
 *  \ingroup Game
 */
class NetworkEventCouplingServer {
  public:
    NetworkEventCouplingServer(int port, const std::shared_ptr<kxm::Game::EventLoopHub> &hub,
                               const std::shared_ptr<K::Core::ThreadPool> &threadPool);
    ~NetworkEventCouplingServer();

  private:
    static const int couplingCompletionId = 0;
    static const int workerCompletionId   = 1;

    class SharedState;
    class Worker;

    std::shared_ptr<SharedState>         sharedState_;

    std::shared_ptr<K::IO::ListenSocket> listenSocket_;
    std::shared_ptr<Worker>              worker_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLINGSERVER_H_
