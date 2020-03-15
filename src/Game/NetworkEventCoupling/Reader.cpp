#include "Reader.h"
#include "SharedState.h"

#include <kxm/Core/Buffer.h>
#include <kxm/Core/logging.h>
#include <K/IO/SocketStream.h>
#include <K/IO/IOTools.h>
#include <kxm/Game/EventLoopHub.h>

using std::shared_ptr;
using std::endl;
using kxm::Core::Log;
using kxm::Core::Buffer;
using K::IO::SocketStream;

namespace kxm {
namespace Game {

NetworkEventCoupling::Reader::Reader(const shared_ptr<SocketStream> &stream, const shared_ptr<EventLoopHub> &hub,
                                     int hubClientId, shared_ptr<SharedState> sharedState)
        : sharedState_(sharedState),
          stream_(stream),
          hub_(hub),
          hubClientId_(hubClientId) {
    // Nop.
}

void NetworkEventCoupling::Reader::ExecuteAction() {
    Log().Stream() << "reader thread spawning..." << endl;

    Buffer buffer;
    bool   badSize = false;
    while (!stream_->IOError() && !stream_->EndOfStream() && !badSize) {
        uint32_t size;
        if (ReadItem(stream_.get(), &size, sizeof(size))) {
            int sizeAsInt = static_cast<int>(size);
            if (sizeAsInt <= 0) {
                badSize = true;
            }
            if (!badSize) {
                buffer.Clear();
                buffer.Append(nullptr, sizeAsInt);
                if (ReadItem(stream_.get(), buffer.Data(), buffer.DataSize())) {
                    hub_->Post(hubClientId_, buffer, true);
                }
            }
        }
    }

    Log().Stream() << "reader thread terminating" << endl;
}

}    // Namespace Game.
}    // Namespace kxm.

