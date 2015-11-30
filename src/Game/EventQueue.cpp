//
//  EventQueue.cpp
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


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
    auto infoIter = idToSlotMap_.find(eventType.id);
    assert(infoIter != idToSlotMap_.end());
    for (EventHandlerInterface *handler : events_[infoIter->second].handlers) {
        assert(handler != handlerToRegister);
    }
    events_[infoIter->second].handlers.push_back(handlerToRegister);
}

void EventQueue::UnregisterHandler(EventHandlerInterface *handlerToUnregister) {
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

void EventQueue::Schedule(const Event &event) {
    int slot = idToSlotMap_[event.Type().id];
    scheduleQueue_->Append(&slot, sizeof(slot));
    event.Serialize(scheduleQueue_.get());
}

bool EventQueue::ProcessEvents() {
    bool terminationRequested = false;
    
    if (!processingEvents_) {
        processingEvents_ = true;
        
        if (!hub_) {
            activeQueue_->Clear();
            activeQueue_.swap(scheduleQueue_);
        }
        else {
            terminationRequested = !hub_->Sync(hubClientId_, &scheduleQueue_, activeQueue_.get(),
                                               hubSyncWaitEnabled_);
        }
        
        Buffer::Reader reader = activeQueue_->GetReader();
        int slot;
        while (reader.ReadBlock(&slot, sizeof(slot))) {
                // The active queue as well as the reader have not been touched as a result of
                // handler calls in earlier iterations. The handler registration on the other hand
                // might have changed, yet the data is valid again.
            EventInfo &info  = events_[slot];
            Event     &event = *(info.prototype);
            event.Deserialize(&reader);
            for (EventHandlerInterface *handler : info.handlers) {
                handlersToCall_.push_back(handler);
            }
            
            // While processing the handlers for this event, the registration for its handlers might
            // change.
            for (EventHandlerInterface *handler : handlersToCall_) {
                handler->HandleEvent(event);
                    // Activating the handlers will probably cause this class instance's methods to
                    // be called. This is okay: This method is protected against re-entry (same
                    // thread) and all other methods are safe to be called while we run to
                    // completion. State we need to remain untouched will not get modified by other
                    // methods, including the prepared event prototypes. Likewise, when we call out
                    // to a handler, state needed by other methods of this class is valid.
            }
            
            handlersToCall_.clear();
        }
        
        processingEvents_ = false;
    }
    
    return !terminationRequested;
}

}    // Namespace Game.
}    // Namespace kxm.