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

EventQueue::EventQueue(int initialBufferSize)
    : activeQueue_(initialBufferSize >= 16 ? initialBufferSize : 16),
      scheduleQueue_(new Buffer(initialBufferSize >= 16 ? initialBufferSize : 16)) {
    // Nop.
}

void EventQueue::RegisterEvent(std::unique_ptr<Event> protoType) {
    assert(protoType.get() != nullptr);
    size_t id             = protoType->Type().id;
    bool   alreadyPresent = (idToSlotMap_.find(id) != idToSlotMap_.end());
    if (alreadyPresent)
        Log().Stream() << "hash collision while registering event \"" << protoType->Type().name
                       << "\"" << std::endl;
    assert(!alreadyPresent);
    int slot = (int)events_.size();
    events_.push_back(EventInfo(std::move(protoType)));
    idToSlotMap_[id] = slot;
}

void EventQueue::AddHandler(const Event::EventType &eventType,
                            const std::shared_ptr<EventHandlerInterface> &handler) {
    auto info = idToSlotMap_.find(eventType.id);
    assert(info != idToSlotMap_.end());
    events_[info->second].handlers.push_back(handler);
}

void EventQueue::Schedule(const Event &event) {
    int slot = idToSlotMap_[event.Type().id];
    scheduleQueue_->Append(&slot, sizeof(slot));
    event.Serialize(scheduleQueue_.get());
}

void EventQueue::ProcessEvents() {
    Buffer::Reader reader = activeQueue_.GetReader();
    int slot;
    while (reader.ReadBlock(&slot, sizeof(slot))) {
        EventInfo &info  = events_[slot];
        Event     &event = *(info.prototype);
        event.Deserialize(&reader);
        for (auto handler : info.handlers)
            handler->HandleEvent(event);
        
        //eventTrace_.push_back(string(event->Type().name));
        //if (eventTrace_.size() == 150) {
        //    for (int i = 0; i < eventTrace_.size(); ++i)
        //        Log(this).Stream() << i << ". " << eventTrace_[i] << endl;
        //}
    }
    activeQueue_.Clear();
}

bool EventQueue::SyncWithHub(EventQueueHub *hub, EventQueueHub::ClientId clientId, bool wait) {
    return hub->Sync(clientId, &scheduleQueue_, &activeQueue_, wait);
}

}    // Namespace Game.
}    // Namespace kxm.