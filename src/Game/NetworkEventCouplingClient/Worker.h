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
           const std::shared_ptr<kxm::Core::ActionInterface> &onConnectedAction,
           const std::shared_ptr<kxm::Core::ActionInterface> &onFailedToConnectAction,
           const std::shared_ptr<kxm::Core::ActionInterface> &onDisconnectedAction,
           const std::shared_ptr<K::Core::ThreadPool> &threadPool, std::shared_ptr<SharedState> sharedState);
    //! Informs the worker about the host to connect to.
    void SetHost(uint32_t ip4Address, int port);
    void ExecuteAction();

  private:
    std::shared_ptr<SharedState>                sharedState_;
    std::shared_ptr<kxm::Game::EventLoopHub>    hub_;
    std::shared_ptr<kxm::Core::ActionInterface> onConnectedAction_;
    std::shared_ptr<kxm::Core::ActionInterface> onFailedToConnectAction_;
    std::shared_ptr<kxm::Core::ActionInterface> onDisconnectedAction_;
    std::shared_ptr<K::Core::ThreadPool>        threadPool_;
    uint32_t                                    hostIp4Address_;
    int                                         hostPort_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLINGCLIENT_WORKER_H_
