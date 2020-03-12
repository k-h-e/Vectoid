#include <kxm/Game/NetworkEventCouplingClient.h>

#include <K/Core/ThreadPool.h>
#include <kxm/Core/logging.h>
#include "SharedState.h"
#include "Worker.h"

using std::shared_ptr;
using std::make_shared;
using std::thread;
using std::endl;
using K::Core::ThreadPool;
using kxm::Core::Log;

namespace kxm {
namespace Game {

NetworkEventCouplingClient::NetworkEventCouplingClient(const shared_ptr<EventLoopHub> &hub,
                                                       const shared_ptr<ThreadPool> &threadPool)
        : threadPool_(threadPool) {
    sharedState_ = make_shared<SharedState>();
    worker_      = make_shared<Worker>(hub, sharedState_);
}

NetworkEventCouplingClient::~NetworkEventCouplingClient() {
    sharedState_->WaitForConnection();
}

void NetworkEventCouplingClient::Connect(uint32_t ip4Address, int port) {
    sharedState_->WaitForConnection();
    sharedState_->PrepareToConnect();
    threadPool_->Run(worker_, sharedState_);
}

void NetworkEventCouplingClient::Disconnect() {

}

}    // Namespace Game.
}    // Namespace kxm.

