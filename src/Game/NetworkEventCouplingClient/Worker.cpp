#include "Worker.h"

#include "SharedState.h"
#include <kxm/Core/logging.h>

using std::shared_ptr;
using std::unique_ptr;
using std::endl;
using kxm::Core::Log;

namespace kxm {
namespace Game {

NetworkEventCouplingClient::Worker::Worker(const shared_ptr<EventLoopHub> &hub, shared_ptr<SharedState> sharedState)
        : sharedState_(sharedState),
          hub_(hub) {
    // Nop.
}

void NetworkEventCouplingClient::Worker::ExecuteAction() {
    Log().Stream() << "connector spawning..." << endl;

    Log().Stream() << "connector terminating" << endl;
}

}    // Namespace Game.
}    // Namespace kxm.

