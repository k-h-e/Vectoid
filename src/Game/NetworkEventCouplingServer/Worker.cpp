#include "Worker.h"

#include "SharedState.h"
#include <kxm/Game/NetworkEventCoupling.h>
#include <kxm/Core/logging.h>

using std::shared_ptr;
using std::unique_ptr;
using std::endl;
using kxm::Core::Log;
using K::IO::ListenSocket;
using K::IO::SocketStream;
using kxm::Game::NetworkEventCoupling;

namespace kxm {
namespace Game {

NetworkEventCouplingServer::Worker::Worker(int port, const shared_ptr<EventLoopHub> &hub,
                                           const shared_ptr<SharedState> &sharedState)
        : sharedState_(sharedState),
          hub_(hub) {
    listenSocket_ = unique_ptr<ListenSocket>(new ListenSocket(port));
}

void NetworkEventCouplingServer::Worker::Run() {
    Log().Stream() << "worker thread spawning..." << endl;

    while (true) {
        Log().Stream() << "waiting for client to connect..." << endl;
        shared_ptr<SocketStream> stream = listenSocket_->Accept();
        if (stream) {
            auto coupling = unique_ptr<NetworkEventCoupling>(new NetworkEventCoupling(stream, hub_));
            coupling->RegisterCompletionHandler(*sharedState_.get(), 666);
            Log().Stream() << "waiting for coupling to finish..." << endl;
            sharedState_->WaitForCouplingFinished();
            coupling->UnregisterCompletionHandler(*sharedState_.get());
        }
    }

    Log().Stream() << "worker thread terminating" << endl;
}

}    // Namespace Game.
}    // Namespace kxm.

