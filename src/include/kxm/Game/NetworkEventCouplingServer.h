#ifndef KXM_GAME_NETWORKEVENTCOUPLINGSERVER_H_
#define KXM_GAME_NETWORKEVENTCOUPLINGSERVER_H_

#include <memory>
#include <thread>

namespace kxm {
namespace Game {

class EventLoopHub;

//! Installs network event couplings for incoming network connections.
/*!
 *  \ingroup Game
 */
class NetworkEventCouplingServer {
  public:
    NetworkEventCouplingServer(int port, const std::shared_ptr<kxm::Game::EventLoopHub> &hub);
    ~NetworkEventCouplingServer();

  private:
    class SharedState;
    class Worker;

    std::shared_ptr<SharedState> sharedState_;
    std::shared_ptr<Worker>      worker_;

    std::shared_ptr<std::thread> workerThread_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLINGSERVER_H_
