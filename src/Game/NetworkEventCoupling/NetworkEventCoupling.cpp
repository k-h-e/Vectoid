#include <kxm/Game/NetworkEventCoupling.h>

#include "SharedState.h"
#include "Reader.h"
#include "Writer.h"

using std::shared_ptr;
using std::make_shared;
using std::thread;

namespace kxm {
namespace Game {

NetworkEventCoupling::NetworkEventCoupling(const shared_ptr<EventLoopHub> &hub) {
    sharedState_ = make_shared<SharedState>();
    reader_      = make_shared<Reader>(hub, sharedState_);
    writer_      = make_shared<Writer>(hub, sharedState_);

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

