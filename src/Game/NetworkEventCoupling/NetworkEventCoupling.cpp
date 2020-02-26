#include <kxm/Game/NetworkEventCoupling.h>

#include <kxm/Core/logging.h>
#include <K/IO/SocketStream.h>
#include <kxm/Game/EventLoopHub.h>
#include "SharedState.h"
#include "Reader.h"
#include "Writer.h"

using std::shared_ptr;
using std::make_shared;
using std::thread;
using std::hex;
using std::dec;
using std::endl;
using K::Core::CompletionHandlerInterface;
using kxm::Core::Log;
using K::IO::SocketStream;

namespace kxm {
namespace Game {

NetworkEventCoupling::NetworkEventCoupling(const shared_ptr<SocketStream> &stream,
                                           const shared_ptr<EventLoopHub> &hub) {
    int hubClientId = hub->AddEventLoop();

    sharedState_ = make_shared<SharedState>();
    stream_      = stream;
    reader_      = make_shared<Reader>(stream, hub, hubClientId, sharedState_);
    writer_      = make_shared<Writer>(stream, hub, hubClientId, sharedState_);

    auto reader = reader_;
    readerThread_ = make_shared<thread>([=]{ reader->Run(); });
    auto writer = writer_;
    writerThread_ = make_shared<thread>([=]{ writer->Run(); });

    Log().Stream() << "network event coupling 0x" << hex << this << dec << " installed" << endl;
}

NetworkEventCoupling::~NetworkEventCoupling() {
    Log().Stream() << "network event coupling 0x" << hex << this << dec << " shutting down..." << endl;
    stream_->Close();
    readerThread_->join();
    writerThread_->join();
    Log().Stream() << "network event coupling 0x" << hex << this << dec << " uninstalled" << endl;
}

void NetworkEventCoupling::RegisterCompletionHandler(CompletionHandlerInterface &handler, int operationId) {
    sharedState_->RegisterCompletionHandler(handler, operationId);
}

void NetworkEventCoupling::UnregisterCompletionHandler(CompletionHandlerInterface &handler) {
    sharedState_->UnregisterCompletionHandler(handler);
}

}    // Namespace Game.
}    // Namespace kxm.

