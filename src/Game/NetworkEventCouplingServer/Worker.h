#ifndef KXM_GAME_NETWORKEVENTCOUPLINGSERVER_WORKER_H_
#define KXM_GAME_NETWORKEVENTCOUPLINGSERVER_WORKER_H_

#include <kxm/Core/ActionInterface.h>
#include <kxm/Game/NetworkEventCouplingServer.h>

namespace K {
namespace IO {
    class ListenSocket;
}
}

namespace kxm {
namespace Game {

class EventLoopHub;

//! Worker for the network event coupling server.
/*!
 *  \ingroup Game
 */
class NetworkEventCouplingServer::Worker : public virtual kxm::Core::ActionInterface {
  public:
    Worker(const std::shared_ptr<K::IO::ListenSocket> &listenSocket,
           const std::shared_ptr<kxm::Game::EventLoopHub> &hub,
           const std::shared_ptr<K::Core::ThreadPool> &threadPool, const std::shared_ptr<SharedState> &sharedState);
    void ExecuteAction();

  private:
    std::shared_ptr<SharedState>             sharedState_;

    std::shared_ptr<K::IO::ListenSocket>     listenSocket_;
    std::shared_ptr<kxm::Game::EventLoopHub> hub_;
    std::shared_ptr<K::Core::ThreadPool>     threadPool_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLINGSERVER_WORKER_H_
