#include "Runner.h"

#include <kxm/Core/ActionInterface.h>
#include <K/Core/CompletionHandlerInterface.h>
#include <kxm/Core/logging.h>
#include "SharedRunnerState.h"

using std::shared_ptr;
using std::endl;
using kxm::Core::ActionInterface;
using K::Core::CompletionHandlerInterface;
using kxm::Core::Log;

namespace K {
namespace Core {

ThreadPool::Runner::Runner(int thread, CompletionHandlerInterface &completionHandler,
                           const shared_ptr<SharedRunnerState> &sharedState)
        : sharedState_(sharedState),
          thread_(thread),
          completionHandler_(completionHandler) {
    // Nop.
}

void ThreadPool::Runner::Run() {
    Log(this).Stream() << "runner spawning..." << endl;

    shared_ptr<ActionInterface>            action;
    shared_ptr<CompletionHandlerInterface> completionHandler;
    while (sharedState_->WaitForWork(&action, &completionHandler)) {
        Log(this).Stream() << "runner calling action..." << endl;
        if (action) {    // TODO: remove!
            action->ExecuteAction();
        }
        action.reset();
        if (completionHandler) {
            Log(this).Stream() << "runner calling completion handler..." << endl;
            completionHandler->OnCompletion(0);
            completionHandler.reset();
        }
        completionHandler_.OnCompletion(thread_);
    }

    Log(this).Stream() << "runner terminating" << endl;
}

}    // Namespace Core.
}    // Namespace K.

