#ifndef KXM_GAME_NETWORKEVENTCOUPLING_SHAREDSTATE_H_
#define KXM_GAME_NETWORKEVENTCOUPLING_SHAREDSTATE_H_

#include <unordered_map>
#include <mutex>
#include <K/Core/CompletionNotifierInterface.h>
#include <kxm/Game/NetworkEventCoupling.h>

namespace kxm {
namespace Game {

//! State shared between threads of the network event coupling.
/*!
 *  \ingroup Game
 *
 *  The class is thread-safe (i.e. all public methods).
 */
class NetworkEventCoupling::SharedState : public K::Core::CompletionNotifierInterface {
  public:
    SharedState();
    virtual void RegisterCompletionHandler(K::Core::CompletionHandlerInterface &handler, int operationId);
    virtual void UnregisterCompletionHandler(K::Core::CompletionHandlerInterface &handler);
    void OnReaderFinished();
    void OnWriterFinished();

  private:
    void ProcessCompletionHandlers();

    std::mutex                                                     lock_;
    std::unordered_map<K::Core::CompletionHandlerInterface *, int> completionHandlers_;
    bool                                                           readerFinished_;
    bool                                                           writerFinished_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLING_SHAREDSTATE_H_
