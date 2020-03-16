#include <kxm/Game/NetworkEventCouplingServer.h>

#include <K/Core/ThreadPool.h>
#include "SharedState.h"
#include "Worker.h"

using std::shared_ptr;
using std::make_shared;
using K::Core::ThreadPool;

namespace kxm {
namespace Game {

NetworkEventCouplingServer::NetworkEventCouplingServer(int port, const shared_ptr<EventLoopHub> &hub,
                                                       const shared_ptr<ThreadPool> &threadPool) {
    sharedState_ = make_shared<SharedState>();
    worker_      = make_shared<Worker>(port, hub, threadPool, sharedState_);

    threadPool->Run(worker_, sharedState_, workerCompletionId);
}

NetworkEventCouplingServer::~NetworkEventCouplingServer() {

    // TODO: Ask worker to terminate.

    sharedState_->WaitForWorkerFinished();
}

}    // Namespace Game.
}    // Namespace kxm.

