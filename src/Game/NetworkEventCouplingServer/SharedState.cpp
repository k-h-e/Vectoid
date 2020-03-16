#include "SharedState.h"

#include <K/Core/Log.h>

using std::unique_lock;
using std::mutex;
using std::to_string;
using K::Core::Log;

namespace kxm {
namespace Game {

NetworkEventCouplingServer::SharedState::SharedState()
        : couplingFinished_(false),
          workerFinished_(false) {
    // Nop.
}

void NetworkEventCouplingServer::SharedState::OnCompletion(int completionId) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    if (completionId == couplingCompletionId) {
        couplingFinished_ = true;
        Log::Print(Log::Level::Debug, this, [&]{ return "coupling signalled completion"; });
    }
    else if (completionId == workerCompletionId) {
        workerFinished_ = true;
    }
    stateChanged_.notify_all();
}    // ... critical section, end.

void NetworkEventCouplingServer::SharedState::WaitForCouplingFinished() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    while (true) {
        if (couplingFinished_) {
            couplingFinished_ = false;
            return;
        }
        stateChanged_.wait(critical);
    }
}    // ... critical section, end.

void NetworkEventCouplingServer::SharedState::WaitForWorkerFinished() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    while (!workerFinished_) {
        stateChanged_.wait(critical);
    }
}    // ... critical section, end.

}    // Namespace Game.
}    // Namespace kxm.

