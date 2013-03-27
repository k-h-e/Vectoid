//
//  EventQueueCore.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//


#include <kxm/Game/EventQueueCore.h>

#include <kxm/Core/logging.h>
#include <kxm/Game/Event.h>
#include <kxm/Game/PoolInterface.h>
#include <kxm/Game/EventHandlerInterface.h>

using namespace std;
using namespace boost;
using namespace kxm::Core;


namespace kxm {
namespace Game {

EventQueueCore::EventQueueCore()
        : schedulingQueue_(0) {
}

int EventQueueCore::RegisterEventPool(shared_ptr<PoolInterface<Event> > pool) {
    int poolId = (int)pools_.size();
    pools_.push_back(pool);
    return poolId;
}

void EventQueueCore::RegisterEventType(int eventType, int pool) {
    assert((pool >= 0) && (pool < (int)pools_.size()));
    while ((int)eventTypes_.size() <= eventType)
        eventTypes_.push_back(EventTypeInfo(-1));
    eventTypes_[eventType] = EventTypeInfo(pool);
}

void EventQueueCore::RegisterEventHandler(int eventType, EventHandlerInterface *eventHandler) {
    assert(   (eventType >= 0) && (eventType < (int)eventTypes_.size())
           && (eventTypes_[eventType].pool != -1));
    eventTypes_[eventType].handlers.push_back(eventHandler);
}

Event &EventQueueCore::ScheduleEvent(int eventType) {
    assert(   (eventType >= 0) && (eventType < (int)eventTypes_.size())
           && (eventTypes_[eventType].pool != -1));
    int pool = eventTypes_[eventType].pool,
        itemId;
    Event &event = pools_[pool]->Get(&itemId);
    event.type_  = eventType;
    events_[schedulingQueue_].push_back(EventInfo(pool, itemId));
    return event;
}

void EventQueueCore::ProcessEvents() {
    vector<EventInfo> &eventsToProcess = events_[schedulingQueue_];
    schedulingQueue_ = 1 - schedulingQueue_;
    
    for (vector<EventInfo>::iterator iter = eventsToProcess.begin(); iter != eventsToProcess.end();
         ++iter) {
        Event &event = pools_[iter->pool]->Access(iter->itemId);
        vector<EventHandlerInterface *> &handlers = eventTypes_[event.type_].handlers;
        for (vector<EventHandlerInterface *>::iterator iter = handlers.begin();
             iter != handlers.end(); ++iter)
            (*iter)->HandleEvent(event);
        //printf("called %d handlers for event (%d,%d)\n", (int)handlers.size(), iter->pool,
        //    iter->itemId);
        pools_[iter->pool]->Put(iter->itemId);
    }
    //printf("processed %d events\n", (int)eventsToProcess.size());
    eventsToProcess.clear();
}

}    // Namespace Game.
}    // Namespace kxm.

