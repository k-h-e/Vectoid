#ifndef KXM_GAME_NETWORKEVENTCOUPLINGCLIENT_H_
#define KXM_GAME_NETWORKEVENTCOUPLINGCLIENT_H_

#include <memory>

namespace K {
namespace Core {
    class ThreadPool;
}
}

namespace kxm {
namespace Core {
    class ActionInterface;
}
}

namespace kxm {
namespace Game {

class EventLoopHub;

//! Establishes network connections (at most one at a time) to remote event loop mechanisms and installs local network
//! event couplings for them.
/*!
 *  \ingroup Game
 */
class NetworkEventCouplingClient {
  public:
    //! Constructor.
    /*!
     *  \param onConnectAction
     *  Optional. If present, gets called on an arbitrary thread whenever a connection is established.
     *
     *  \param onDisconnectAction
     *  Optional. If present, gets called on an arbitrary thread whenever a connection has been closed or has broken
     *  down.
     */
    NetworkEventCouplingClient(
        const std::shared_ptr<kxm::Game::EventLoopHub> &hub,
        const std::shared_ptr<kxm::Core::ActionInterface> &onConnectAction,
        const std::shared_ptr<kxm::Core::ActionInterface> &onDisconnectAction,
        const std::shared_ptr<K::Core::ThreadPool> &threadPool);
    ~NetworkEventCouplingClient();
    //! Establishes a network event coupling connection to the specified host.
    /*!
     *  The connection is established in the background, so when this method returns this does not mean that the
     *  connection is already up.
     */
    void Connect(uint32_t ip4Address, int port);
    //! Disconnects the network event coupling connection (if one is present or in the process of being established).
    void Disconnect();

  private:
    static const int workerCompletionId = 0;
    class SharedState;
    class Worker;

    std::shared_ptr<SharedState>         sharedState_;

    std::shared_ptr<Worker>              worker_;
    std::shared_ptr<K::Core::ThreadPool> threadPool_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLINGCLIENT_H_
