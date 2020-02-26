#include "SharedState.h"

#include <K/Core/CompletionHandlerInterface.h>
#include <kxm/Core/logging.h>

using std::unique_lock;
using std::mutex;
using std::endl;
using K::Core::CompletionHandlerInterface;
using kxm::Core::Log;

namespace kxm {
namespace Game {

NetworkEventCoupling::SharedState::SharedState()
        : readerFinished_(false),
          writerFinished_(false) {
    // Nop.
}

void NetworkEventCoupling::SharedState::RegisterCompletionHandler(CompletionHandlerInterface &handler,
                                                                  int operationId) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    completionHandlers_[&handler] = operationId;
    Log().Stream() << "added completion handler, num=" << completionHandlers_.size() << endl;
}    // ... critical section, end.

void NetworkEventCoupling::SharedState::UnregisterCompletionHandler(CompletionHandlerInterface &handler) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    completionHandlers_.erase(&handler);
    Log().Stream() << "removed completion handler, num=" << completionHandlers_.size() << endl;
}    // ... critical section, end.

void NetworkEventCoupling::SharedState::OnReaderFinished() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    if (!readerFinished_) {
        readerFinished_ = true;
        ProcessCompletionHandlers();
    }
}    // ... critical section, end.

void NetworkEventCoupling::SharedState::OnWriterFinished() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    if (!writerFinished_) {
        writerFinished_ = true;
        ProcessCompletionHandlers();
    }
}    // ... critical section, end.

// Expects lock to be held.
void NetworkEventCoupling::SharedState::ProcessCompletionHandlers() {
    if (readerFinished_ && writerFinished_) {
        for (auto &pair : completionHandlers_) {
            Log().Stream() << "notifying..." << endl;
            pair.first->OnCompletion(pair.second);
        }
        Log().Stream() << "notified " << completionHandlers_.size() << " completion handlers" << endl;
    }
}

}    // Namespace Game.
}    // Namespace kxm.

