#include "Writer.h"

#include <kxm/Core/logging.h>
#include <kxm/Game/EventLoopHub.h>

using std::shared_ptr;
using std::endl;
using kxm::Core::Buffer;
using kxm::Core::Log;
using K::IO::SocketStream;

namespace kxm {
namespace Game {

NetworkEventCoupling::Writer::Writer(const shared_ptr<EventLoopHub> &hub, shared_ptr<SharedState> sharedState)
    : sharedState_(sharedState),
      hub_(hub),
      hubClientId_(hub_->AddEventLoop()),
      events_(new Buffer()) {

}

void NetworkEventCoupling::Writer::Run() {
    Log().Stream() << "writer thread spawning..." << endl;

    shared_ptr<StreamSocket> stream;
    while (hub_->GetEvents(hubClientId_, &events_)) {
        if (!stream) {
            stream = sharedState_->GetStream();
            if (!stream) {
                continue;
            }
        }


    }

    Log().Stream() << "writer thread terminating" << endl;
}

}    // Namespace Game.
}    // Namespace kxm.

