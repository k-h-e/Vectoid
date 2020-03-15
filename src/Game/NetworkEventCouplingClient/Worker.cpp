#include "Worker.h"

#include "SharedState.h"
#include <kxm/Core/logging.h>
#include <K/IO/SocketStream.h>
#include <kxm/Game/NetworkEventCoupling.h>

using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;
using std::endl;
using K::Core::ThreadPool;
using kxm::Core::Log;
using K::IO::SocketStream;
using kxm::Game::NetworkEventCoupling;

namespace kxm {
namespace Game {

NetworkEventCouplingClient::Worker::Worker(
    const shared_ptr<EventLoopHub> &hub, const shared_ptr<ThreadPool> &threadPool, shared_ptr<SharedState> sharedState)
        : sharedState_(sharedState),
          hub_(hub),
          threadPool_(threadPool),
          hostIp4Address_(0u),
          hostPort_(0) {
    // Nop.
}

void NetworkEventCouplingClient::Worker::SetHost(uint32_t ip4Address, int port) {
    hostIp4Address_ = ip4Address;
    hostPort_       = port;
}

void NetworkEventCouplingClient::Worker::ExecuteAction() {
    Log().Stream() << "connector spawning..." << endl;

    shared_ptr<NetworkEventCoupling> coupling;
    shared_ptr<SocketStream> socketStream = SocketStream::ConnectToHost(hostIp4Address_, hostPort_);
    if (socketStream) {
        coupling = make_shared<NetworkEventCoupling>(socketStream, hub_, nullptr, 0, threadPool_);
    }
    sharedState_->OnCouplingCreated(coupling);

    Log().Stream() << "connector terminating" << endl;
}

}    // Namespace Game.
}    // Namespace kxm.

