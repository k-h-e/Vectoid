#include "Reader.h"

#include <kxm/Core/logging.h>

using std::shared_ptr;
using std::endl;
using kxm::Core::Log;

namespace kxm {
namespace Game {

NetworkEventCoupling::Reader::Reader(const shared_ptr<EventLoopHub> &hub, shared_ptr<SharedState> sharedState)
    : sharedState_(sharedState),
      hub_(hub) {

}

void NetworkEventCoupling::Reader::Run() {
    Log().Stream() << "reader thread spawning..." << endl;

    Log().Stream() << "reader thread terminating" << endl;
}

}    // Namespace Game.
}    // Namespace kxm.

