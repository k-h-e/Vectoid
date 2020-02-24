#include <kxm/Game/NetworkEventCoupling.h>

#include <kxm/Game/EventLoopHub.h>
#include "SharedState.h"
#include "Reader.h"
#include "Writer.h"

using std::shared_ptr;
using std::make_shared;
using std::thread;
using K::IO::SocketStream;

namespace kxm {
namespace Game {

NetworkEventCoupling::NetworkEventCoupling(const shared_ptr<SocketStream> &stream,
                                           const shared_ptr<EventLoopHub> &hub) {
    int hubClientId = hub->AddEventLoop();

    sharedState_ = make_shared<SharedState>();
    reader_      = make_shared<Reader>(stream, hub, hubClientId, sharedState_);
    writer_      = make_shared<Writer>(stream, hub, hubClientId, sharedState_);

    auto reader = reader_;
    readerThread_ = make_shared<thread>([=]{ reader->Run(); });
    auto writer = writer_;
    writerThread_ = make_shared<thread>([=]{ writer->Run(); });
}

NetworkEventCoupling::~NetworkEventCoupling() {
    readerThread_->join();
    writerThread_->join();
}

}    // Namespace Game.
}    // Namespace kxm.

