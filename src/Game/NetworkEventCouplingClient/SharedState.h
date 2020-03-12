#ifndef KXM_GAME_NETWORKEVENTCOUPLINGCLIENT_SHAREDSTATE_H_
#define KXM_GAME_NETWORKEVENTCOUPLINGCLIENT_SHAREDSTATE_H_

#include <memory>
#include <mutex>
#include <condition_variable>
#include <K/Core/CompletionHandlerInterface.h>
#include <kxm/Game/NetworkEventCoupling.h>
#include <kxm/Game/NetworkEventCouplingClient.h>

namespace kxm {
namespace Game {

//! State shared between threads of the network event coupling client.
/*!
 *  \ingroup Game
 *
 *  The class is thread-safe (i.e. all public methods).
 */
class NetworkEventCouplingClient::SharedState : public virtual K::Core::CompletionHandlerInterface {
  public:
    SharedState();
    void PrepareToConnect();
    void WaitForConnection();
    void OnCompletion(int operationId);

  private:
    std::mutex                            lock_;
    std::condition_variable               stateChanged_;
    std::unique_ptr<NetworkEventCoupling> coupling_;
    bool                                  connecting_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLINGCLIENT_SHAREDSTATE_H_
