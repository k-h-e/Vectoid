#include <kxm/Game/NetworkEventCoupling.h>

#include <K/Core/ThreadPool.h>
#include <kxm/Core/logging.h>
#include <K/IO/SocketStream.h>
#include <kxm/Game/EventLoopHub.h>
#include "SharedState.h"
#include "Reader.h"
#include "Writer.h"

using std::shared_ptr;
using std::make_shared;
using std::hex;
using std::dec;
using std::endl;
using K::Core::CompletionHandlerInterface;
using K::Core::ThreadPool;
using kxm::Core::Log;
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

    threadPool->Run(reader_, sharedState_, ReaderCompletionId);
    threadPool->Run(writer_, sharedState_, WriterCompletionId);

    Log().Stream() << "network event coupling 0x" << hex << this << dec << " installed" << endl;
}

NetworkEventCoupling::~NetworkEventCoupling() {
    Log().Stream() << "network event coupling 0x" << hex << this << dec << " shutting down..." << endl;
    stream_->Close();
    sharedState_->WaitForThreadsFinished();
    Log().Stream() << "network event coupling 0x" << hex << this << dec << " uninstalled" << endl;
}

}    // Namespace Game.
}    // Namespace kxm.

