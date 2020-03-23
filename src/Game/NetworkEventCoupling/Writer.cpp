#include "Writer.h"
#include "SharedState.h"

#include <K/Core/Log.h>
#include <kxm/Game/EventLoopHub.h>
#include <K/IO/SocketStream.h>
#include <K/IO/IOTools.h>

using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;
using kxm::Core::Buffer;
using K::Core::Log;
using K::IO::SocketStream;

namespace kxm {
namespace Game {

NetworkEventCoupling::Writer::Writer(const shared_ptr<SocketStream> &stream, const shared_ptr<EventLoopHub> &hub,
                                     int hubClientId, shared_ptr<SharedState> sharedState)
        : sharedState_(sharedState),
          stream_(stream),
          hub_(hub),
          hubClientId_(hubClientId) {
    // Nop.
}

void NetworkEventCoupling::Writer::ExecuteAction() {
    Log::Print(Log::Level::Debug, this, []{ return "spawning..."; });

    unique_ptr<Buffer> buffer(new Buffer());
    while (!stream_->Error() && hub_->GetEvents(hubClientId_, &buffer, false)) {
        int dataSize = buffer->DataSize();
        if (dataSize > 0) {    // Defensive, shouldn't be necessary.
            uint32_t size = dataSize;
            WriteItem(stream_.get(), &size, sizeof(size));
            WriteItem(stream_.get(), buffer->Data(), dataSize);
        }
    }

    Log::Print(Log::Level::Debug, this, []{ return "terminating"; });
}

}    // Namespace Game.
}    // Namespace kxm.

