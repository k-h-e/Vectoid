//
//  EventQueueCore.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//


#include <kxm/Game/OldEventQueueCore.h>

#include <cassert>

#include <kxm/Core/Buffer.h>
#include <kxm/Core/logging.h>
#include <kxm/Game/OldEvent.h>
#include <kxm/Game/PoolInterface.h>
#include <kxm/Game/EventHandlerInterface.h>

using namespace std;
using namespace kxm::Core;


namespace kxm {
namespace Game {

OldEventQueueCore::OldEventQueueCore()
        : schedulingQueue_(0) {
}

int OldEventQueueCore::RegisterEventPool(shared_ptr<PoolInterface<OldEvent>> pool) {
    int poolId = (int)pools_.size();
    pools_.push_back(pool);
    return poolId;
}

void OldEventQueueCore::RegisterEventType(int eventType, int pool) {
    assert((pool >= 0) && (pool < (int)pools_.size()));
    while ((int)eventTypes_.size() <= eventType)
        eventTypes_.push_back(EventTypeInfo(-1));
    eventTypes_[eventType] = EventTypeInfo(pool);
}

void OldEventQueueCore::RegisterEventHandler(
        int eventType, const shared_ptr<EventHandlerInterface> &eventHandler) {
    assert(   (eventType >= 0) && (eventType < (int)eventTypes_.size())
           && (eventTypes_[eventType].pool != -1));
    eventTypes_[eventType].handlers.push_back(eventHandler);
}

OldEvent &OldEventQueueCore::ScheduleEvent(int eventType) {
    assert(   (eventType >= 0) && (eventType < (int)eventTypes_.size())
           && (eventTypes_[eventType].pool != -1));
    int pool = eventTypes_[eventType].pool,
        itemId;
    OldEvent &event = pools_[pool]->Get(&itemId);
    event.type_      = eventType;
    events_[schedulingQueue_].push_back(EventInfo(pool, itemId));
    return event;
}

void OldEventQueueCore::ProcessEvents() {
    vector<EventInfo> &eventsToProcess = events_[schedulingQueue_];
    schedulingQueue_ = 1 - schedulingQueue_;
    
    for (vector<EventInfo>::iterator iter = eventsToProcess.begin(); iter != eventsToProcess.end();
         ++iter) {
        OldEvent &event = pools_[iter->pool]->Access(iter->itemId);
        vector<shared_ptr<EventHandlerInterface >> &handlers = eventTypes_[event.type_].handlers;
        for (vector<shared_ptr<EventHandlerInterface>>::iterator iter = handlers.begin();
             iter != handlers.end(); ++iter)
            (*iter)->HandleEvent(event);
        pools_[iter->pool]->Put(iter->itemId);
    }
    eventsToProcess.clear();
}

void OldEventQueueCore::SerializeScheduledEvents(Buffer *targetBuffer) {
    vector<EventInfo> &scheduledEvents = events_[schedulingQueue_];
    for (vector<EventInfo>::iterator iter = scheduledEvents.begin(); iter != scheduledEvents.end();
         ++iter) {
        OldEvent &event = pools_[iter->pool]->Access(iter->itemId);
        event.Serialize(targetBuffer);
    }
}

void OldEventQueueCore::DeserializeAndScheduleEvents(const Buffer &buffer) {
    Buffer::Reader reader = buffer.GetReader();
    int type;
    while (reader.Read(&type, sizeof(type)) == sizeof(type)) {
        OldEvent &event = ScheduleEvent(type);
        event.Deserialize(&reader);
    }
}

}    // Namespace Game.
}    // Namespace kxm.

