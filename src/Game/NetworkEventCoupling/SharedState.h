#ifndef KXM_GAME_NETWORKEVENTCOUPLING_SHAREDSTATE_H_
#define KXM_GAME_NETWORKEVENTCOUPLING_SHAREDSTATE_H_

#include <mutex>
#include <condition_variable>
#include <K/Core/CompletionHandlerInterface.h>
#include <kxm/Game/NetworkEventCoupling.h>

namespace kxm {
namespace Game {

//! State shared between threads of the network event coupling.
/*!
 *  \ingroup Game
 *
 *  The class is thread-safe (i.e. all public methods).
 */
class NetworkEventCoupling::SharedState : public virtual K::Core::CompletionHandlerInterface {
  public:
    SharedState(const std::shared_ptr<K::Core::CompletionHandlerInterface> &completionHandler,
                int completionId);
    void WaitForThreadsFinished();
    void OnCompletion(int completionId);

  private:
    std::mutex                                           lock_;
    std::condition_variable                              stateChanged_;
    std::shared_ptr<K::Core::CompletionHandlerInterface> completionHandler_;
    int                                                  completionId_;
    bool                                                 readerFinished_;
    bool                                                 writerFinished_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLING_SHAREDSTATE_H_
