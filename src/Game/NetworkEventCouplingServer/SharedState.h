#ifndef KXM_GAME_NETWORKEVENTCOUPLINGSERVER_SHAREDSTATE_H_
#define KXM_GAME_NETWORKEVENTCOUPLINGSERVER_SHAREDSTATE_H_

#include <mutex>
#include <condition_variable>
#include <K/Core/CompletionHandlerInterface.h>
#include <kxm/Game/NetworkEventCouplingServer.h>

namespace kxm {
namespace Game {

//! State shared between threads of the network event coupling server.
/*!
 *  \ingroup Game
 *
 *  The class is thread-safe (i.e. all public methods).
 */
class NetworkEventCouplingServer::SharedState : public K::Core::CompletionHandlerInterface {
  public:
    SharedState();
    virtual void OnCompletion(int operationId);
    void WaitForCouplingFinished();
    void WaitForWorkerFinished();

  private:
    std::mutex              lock_;
    std::condition_variable stateChanged_;
    bool                    couplingFinished_;
    bool                    workerFinished_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLINGSERVER_SHAREDSTATE_H_
