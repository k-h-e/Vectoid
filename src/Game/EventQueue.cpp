#include <Game/EventQueue.h>

#include <cassert>
#include <kxm/Core/logging.h>
#include <Game/Event.h>

using namespace std;
using namespace kxm::Core;

namespace kxm {
namespace Game {

EventQueue::EventQueue(int initialBufferSize, shared_ptr<EventQueueHub> hub,
                       bool hubSyncWaitEnabled)
    : activeQueue_(new Buffer(initialBufferSize >= 16 ? initialBufferSize : 16)),
      scheduleQueue_(new Buffer(initialBufferSize >= 16 ? initialBufferSize : 16)),
      hub_(hub),
      hubClientId_(!hub ? 0 : hub->AllocUniqueClientId()),
      processingEvents_(false),
      hubSyncWaitEnabled_(hubSyncWaitEnabled) {
    // Nop.
}

void EventQueue::RegisterEvent(std::unique_ptr<Event> protoType) {
    assert(!processingEvents_);
    assert(protoType.get() != nullptr);
    size_t id             = protoType->Type().id;
    bool   alreadyPresent = (idToSlotMap_.find(id) != idToSlotMap_.end());
    if (alreadyPresent)
        Log().Stream() << "hash collision while registering event \"" << protoType->Type().name
                       << "\"" << endl;
    assert(!alreadyPresent);
    int slot = (int)events_.size();
    events_.push_back(EventInfo(std::move(protoType)));
    idToSlotMap_[id] = slot;
}

void EventQueue::RegisterHandler(const Event::EventType &eventType,
                                 EventHandlerInterface *handlerToRegister) {
    assert(!processingEvents_);
    auto infoIter = idToSlotMap_.find(eventType.id);
    assert(infoIter != idToSlotMap_.end());
    for (EventHandlerInterface *handler : events_[infoIter->second].handlers) {
        assert(handler != handlerToRegister);
    }
    events_[infoIter->second].handlers.push_back(handlerToRegister);
}

void EventQueue::UnregisterHandler(EventHandlerInterface *handlerToUnregister) {
    assert(!processingEvents_);
    for (auto &info : events_) {
        vector<EventHandlerInterface *> handlers;
        for (EventHandlerInterface *handler : info.handlers) {
            if (handler != handlerToUnregister) {
                handlers.push_back(handler);
            }
        }
        info.handlers = handlers;
    }
}

// Might get called while ProcessEvents() executes.
void EventQueue::Schedule(const Event &event) {
    int slot = idToSlotMap_[event.Type().id];
    scheduleQueue_->Append(&slot, sizeof(slot));
    event.Serialize(scheduleQueue_.get());
}

bool EventQueue::ProcessEvents() {
    assert(!processingEvents_);
    processingEvents_ = true;
    
    bool terminationRequested = false;
    if (!hub_) {
        activeQueue_->Clear();
        activeQueue_.swap(scheduleQueue_);
    }
    else {
        terminationRequested = !hub_->Sync(hubClientId_, &scheduleQueue_, activeQueue_.get(),
                                           hubSyncWaitEnabled_);
    }
        
    int slot;
    Buffer::Reader reader = activeQueue_->GetReader();
    while (reader.ReadBlock(&slot, sizeof(slot))) {
        EventInfo &info  = events_[slot];
        Event     &event = *(info.prototype);
        event.Deserialize(&reader);
        for (EventHandlerInterface *handler : info.handlers) {
            handler->HandleEvent(event);
        }
    }
        
    processingEvents_ = false;
    return !terminationRequested;
}

}    // Namespace Game.
}    // Namespace kxm.