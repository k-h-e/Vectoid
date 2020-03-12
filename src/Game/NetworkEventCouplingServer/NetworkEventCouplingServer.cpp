#include <kxm/Game/NetworkEventCouplingServer.h>

#include "SharedState.h"
#include "Worker.h"

using std::shared_ptr;
using std::make_shared;
using std::thread;

namespace kxm {
namespace Game {

NetworkEventCouplingServer::NetworkEventCouplingServer(int port, const shared_ptr<EventLoopHub> &hub) {
    sharedState_ = make_shared<SharedState>();
    worker_      = make_shared<Worker>(port, hub, sharedState_);

    auto worker = worker_;
    workerThread_ = make_shared<thread>([=]{ worker->Run(); });
}

NetworkEventCouplingServer::~NetworkEventCouplingServer() {

    // TODO: Ask worker to terminate.

    workerThread_->join();
}

}    // Namespace Game.
}    // Namespace kxm.

