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
    Worker(const std::shared_ptr<kxm::Game::EventLoopHub> &hub, std::shared_ptr<SharedState> sharedState);
    void ExecuteAction();

  private:
    std::shared_ptr<SharedState>             sharedState_;
    std::shared_ptr<kxm::Game::EventLoopHub> hub_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLINGCLIENT_WORKER_H_
