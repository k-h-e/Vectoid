#include "SharedState.h"

namespace kxm {
namespace Game {

shared_ptr<SocketStream> NetworkEventCoupling::SharedState::GetStream() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    return stream_;
}    // ... critical section, end.

}    // Namespace Game.
}    // Namespace kxm.

