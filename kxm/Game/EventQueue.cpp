//
//  EventQueue.cpp
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#include <kxm/Game/EventQueue.h>

#include <cassert>
#include <kxm/Core/logging.h>
#include <kxm/Game/Event.h>

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
}

void EventQueue::ProcessEvents() {
}

void EventQueue::SyncWithHub(EventQueueHub *hub, EventQueueHub::ClientId clientId) {
}

}    // Namespace Game.
}    // Namespace kxm.