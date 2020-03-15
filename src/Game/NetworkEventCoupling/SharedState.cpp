#include "SharedState.h"

#include <K/Core/CompletionHandlerInterface.h>
#include <kxm/Core/logging.h>

using std::shared_ptr;
using std::unique_lock;
using std::mutex;
using std::endl;
using K::Core::CompletionHandlerInterface;
using kxm::Core::Log;

namespace kxm {
namespace Game {

NetworkEventCoupling::SharedState::SharedState(const shared_ptr<CompletionHandlerInterface> &completionHandler,
                                               int completionId)
        : completionHandler_(completionHandler),
          completionId_(completionId),
          readerFinished_(false),
          writerFinished_(false) {
    // Nop.
}

void NetworkEventCoupling::SharedState::WaitForThreadsFinished() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    while (!readerFinished_ || !writerFinished_) {
        stateChanged_.wait(critical);
    }
}    // ... critical section, end.

void NetworkEventCoupling::SharedState::OnCompletion(int completionId) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    if (completionId == ReaderCompletionId) {
        readerFinished_ = true;
    }
    else if (completionId == WriterCompletionId) {
        writerFinished_ = true;
    }

    if (readerFinished_ && writerFinished_) {
        if (completionHandler_) {
            completionHandler_->OnCompletion(completionId_);
            completionHandler_.reset();
        }
    }

    stateChanged_.notify_all();
}    // ... critical section, end.

}    // Namespace Game.
}    // Namespace kxm.

