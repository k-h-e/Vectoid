#ifndef K_CORE_THREADPOOL_H_
#define K_CORE_THREADPOOL_H_

#include <memory>

namespace kxm {
namespace Core {
    class ActionInterface;
}
}

namespace K {
namespace Core {

class CompletionHandlerInterface;

//! Thread pool.
/*!
 *  \ingroup Core
 *
 *  Thread-safe (all public methods).
 */
class ThreadPool {
  public:
    ThreadPool();
    ~ThreadPool();
    //! Runs the specified action on an arbitrary pool thread.
    /*!
     *  \param completionHandler
     *  If given, the completion handler will get called on an arbitrary pool thread when the action has completed.
     */
    void Run(const std::shared_ptr<kxm::Core::ActionInterface> &action,
             const std::shared_ptr<K::Core::CompletionHandlerInterface> &completionHandler);

  private:
    class SharedState;
    class Runner;
    class SharedRunnerState;

    std::shared_ptr<SharedState> sharedState_;
};

}    // Namespace Core.
}    // Namespace K.

#endif    // K_CORE_THREADPOOL_H_
