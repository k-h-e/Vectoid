#include "SharedState.h"

using std::mutex;
using std::unique_lock;

namespace kxm {
namespace Game {

NetworkEventCouplingClient::SharedState::SharedState()
        : connecting_(false) {
    // Nop.
}

void NetworkEventCouplingClient::SharedState::PrepareToConnect() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    coupling_.reset();
    connecting_ = true;
}    // ... critical section, end.

void NetworkEventCouplingClient::SharedState::WaitForConnection() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    while (connecting_) {
        stateChanged_.wait(critical);
    }
}    // ... critical section, end.

void NetworkEventCouplingClient::SharedState::OnCompletion(int operationId) {
    (void)operationId;

    unique_lock<mutex> critical(lock_);    // Critical section...
    connecting_ = false;
    stateChanged_.notify_all();
}    // ... critical section, end.

}    // Namespace Game.
}    // Namespace kxm.

