#include "Worker.h"

#include "SharedState.h"
#include <kxm/Game/NetworkEventCoupling.h>
#include <K/Core/Log.h>

using std::shared_ptr;
using std::unique_ptr;
using K::Core::ThreadPool;
using K::Core::Log;
using K::IO::ListenSocket;
using K::IO::SocketStream;
using kxm::Game::NetworkEventCoupling;

namespace kxm {
namespace Game {

NetworkEventCouplingServer::Worker::Worker(
    int port, const shared_ptr<EventLoopHub> &hub, const shared_ptr<ThreadPool> &threadPool,
    const shared_ptr<SharedState> &sharedState)
        : sharedState_(sharedState),
          hub_(hub),
          threadPool_(threadPool) {
    listenSocket_ = unique_ptr<ListenSocket>(new ListenSocket(port));
}

void NetworkEventCouplingServer::Worker::ExecuteAction() {
    Log::Print(Log::Level::Debug, this, []{ return "spawning..."; });

    while (true) {
        Log::Print(Log::Level::Debug, this, []{ return "waiting for client to connect..."; });
        shared_ptr<SocketStream> stream = listenSocket_->Accept();
        if (stream) {
            auto coupling = unique_ptr<NetworkEventCoupling>(
                new NetworkEventCoupling(stream, hub_, sharedState_, couplingCompletionId, threadPool_));
            Log::Print(Log::Level::Debug, this, []{ return "waiting for coupling to finish..."; });
            sharedState_->WaitForCouplingFinished();
        }
    }

    Log::Print(Log::Level::Debug, this, []{ return "terminating"; });
}

}    // Namespace Game.
}    // Namespace kxm.

