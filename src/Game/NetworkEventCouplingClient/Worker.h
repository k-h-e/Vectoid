#ifndef KXM_GAME_NETWORKEVENTCOUPLINGCLIENT_WORKER_H_
#define KXM_GAME_NETWORKEVENTCOUPLINGCLIENT_WORKER_H_

#include <kxm/Core/ActionInterface.h>
#include <kxm/Game/NetworkEventCouplingClient.h>

namespace kxm {
namespace Game {

class EventLoopHub;

//! Worker for the network event coupling client.
/*!
 *  \ingroup Game
 */
class NetworkEventCouplingClient::Worker : public virtual Core::ActionInterface {
  public:
    Worker(const std::shared_ptr<kxm::Game::EventLoopHub> &hub,
           const std::shared_ptr<kxm::Core::ActionInterface> &onConnectAction,
           const std::shared_ptr<kxm::Core::ActionInterface> &onDisconnectAction,
           const std::shared_ptr<K::Core::ThreadPool> &threadPool, std::shared_ptr<SharedState> sharedState);
    //! Informs the worker about the host to connect to.
    void SetHost(uint32_t ip4Address, int port);
    void ExecuteAction();

  private:
    std::shared_ptr<SharedState>                sharedState_;
    std::shared_ptr<kxm::Game::EventLoopHub>    hub_;
    std::shared_ptr<kxm::Core::ActionInterface> onConnectAction_;
    std::shared_ptr<kxm::Core::ActionInterface> onDisconnectAction_;
    std::shared_ptr<K::Core::ThreadPool>        threadPool_;
    uint32_t                                    hostIp4Address_;
    int                                         hostPort_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLINGCLIENT_WORKER_H_
