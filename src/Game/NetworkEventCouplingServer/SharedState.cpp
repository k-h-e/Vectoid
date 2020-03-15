#include "SharedState.h"

#include <kxm/Core/logging.h>

using std::unique_lock;
using std::mutex;
using std::endl;
using kxm::Core::Log;

namespace kxm {
namespace Game {

NetworkEventCouplingServer::SharedState::SharedState()
        : couplingFinished_(false) {
    // Nop.
}

void NetworkEventCouplingServer::SharedState::OnCompletion(int completionId) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    couplingFinished_ = true;
    stateChanged_.notify_all();
    Log().Stream() << "coupling signalled completion, operation_id=" << completionId << endl;
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

}    // Namespace Game.
}    // Namespace kxm.

