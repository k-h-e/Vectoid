#include <kxm/Game/NetworkEventCoupling.h>

#include <K/Core/ThreadPool.h>
#include <K/Core/Log.h>
#include <K/IO/SocketStream.h>
#include <kxm/Game/EventLoopHub.h>
#include "SharedState.h"
#include "Reader.h"
#include "Writer.h"

using std::shared_ptr;
using std::make_shared;
using K::Core::CompletionHandlerInterface;
using K::Core::ThreadPool;
using K::Core::Log;
using K::IO::SocketStream;

namespace kxm {
namespace Game {

NetworkEventCoupling::NetworkEventCoupling(
        const shared_ptr<SocketStream> &stream, const shared_ptr<EventLoopHub> &hub,
        const shared_ptr<CompletionHandlerInterface> &completionHandler, int completionId,
        const std::shared_ptr<K::Core::ThreadPool> &threadPool) {
    int hubClientId = hub->AddEventLoop();

    sharedState_ = make_shared<SharedState>(completionHandler, completionId);
    stream_      = stream;
    reader_      = make_shared<Reader>(stream, hub, hubClientId, sharedState_);
    writer_      = make_shared<Writer>(stream, hub, hubClientId, sharedState_);

    threadPool->Run(reader_, sharedState_, readerCompletionId);
    threadPool->Run(writer_, sharedState_, writerCompletionId);

    Log::Print(Log::Level::Debug, this, []{ return std::string("installed"); });
}

NetworkEventCoupling::~NetworkEventCoupling() {
    Log::Print(Log::Level::Debug, this, []{ return "shutting down..."; });
    stream_->ShutDown();
    sharedState_->WaitForThreadsFinished();
    Log::Print(Log::Level::Debug, this, []{ return "uninstalled"; });
}

}    // Namespace Game.
}    // Namespace kxm.

