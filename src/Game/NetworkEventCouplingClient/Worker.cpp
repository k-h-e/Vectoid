#include "Worker.h"

#include "SharedState.h"
#include <K/Core/CompletionActionAdapter.h>
#include <K/Core/Log.h>
#include <K/IO/SocketStream.h>
#include <kxm/Game/NetworkEventCoupling.h>

using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;
using K::Core::ThreadPool;
using K::Core::CompletionHandlerInterface;
using K::Core::CompletionActionAdapter;
using K::Core::Log;
using K::IO::SocketStream;
using kxm::Game::NetworkEventCoupling;

namespace kxm {
namespace Game {

NetworkEventCouplingClient::Worker::Worker(
    const shared_ptr<EventLoopHub> &hub, const shared_ptr<ActionInterface> &onConnectAction,
    const shared_ptr<ActionInterface> &onDisconnectAction, const shared_ptr<ThreadPool> &threadPool,
    shared_ptr<SharedState> sharedState)
        : sharedState_(sharedState),
          hub_(hub),
          onConnectAction_(onConnectAction),
          onDisconnectAction_(onDisconnectAction),
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
    Log::Print(Log::Level::Debug, this, []{ return "spawning..."; });

    shared_ptr<NetworkEventCoupling> coupling;
    shared_ptr<SocketStream> socketStream = SocketStream::ConnectToHost(hostIp4Address_, hostPort_);
    if (socketStream) {
        if (onConnectAction_) {
            onConnectAction_->ExecuteAction();
        }
        shared_ptr<CompletionHandlerInterface> handler;
        if (onDisconnectAction_) {
            handler = make_shared<CompletionActionAdapter>(onDisconnectAction_);
        }
        coupling = make_shared<NetworkEventCoupling>(socketStream, hub_, handler, 0, threadPool_);
    }
    sharedState_->OnCouplingCreated(coupling);

    Log::Print(Log::Level::Debug, this, []{ return "terminating"; });
}

}    // Namespace Game.
}    // Namespace kxm.

