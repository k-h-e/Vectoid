#include "SharedRunnerState.h"

using std::shared_ptr;
using std::mutex;
using std::unique_lock;
using kxm::Core::ActionInterface;
using K::Core::CompletionHandlerInterface;

namespace K {
namespace Core {

ThreadPool::SharedRunnerState::SharedRunnerState()
        : shutDownRequested_(false) {
    // Nop.
}

bool ThreadPool::SharedRunnerState::WaitForWork(shared_ptr<ActionInterface> *outAction,
                                                shared_ptr<CompletionHandlerInterface> *outCompletionHandler) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    while (!shutDownRequested_) {
        if (action_) {
            *outAction            = action_;
            *outCompletionHandler = completionHandler_;
            action_.reset();
            completionHandler_.reset();
            return true;
        }

        stateChanged_.wait(critical);
    }

    return false;
}    // ... critical section, end.

void ThreadPool::SharedRunnerState::Execute(const shared_ptr<ActionInterface> &action,
                                            const shared_ptr<CompletionHandlerInterface> &completionHandler) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    action_            = action;
    completionHandler_ = completionHandler;
    stateChanged_.notify_all();
}    // ... critical section, end.

void ThreadPool::SharedRunnerState::RequestShutDown() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    shutDownRequested_ = true;
    stateChanged_.notify_all();
}    // ... critical section, end.

}    // Namespace Core.
}    // Namespace K.

