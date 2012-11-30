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
#include <kxm/Game/EventPoolInterface.h>

using namespace std;
using namespace boost;
using namespace kxm::Core;


namespace kxm {
namespace Game {

EventQueueCore::EventQueueCore()
        : schedulingQueue_(0) {
}

EventQueueCore::~EventQueueCore() {
    for (int i = 0; i < 2; ++i) {
        while (queues_[i].size()) {
            Event *event = queues_[i].front();
            pools_[event->Type()]->Put(event);
            queues_[i].pop_front();
        }
    }
}

void EventQueueCore::RegisterEventType(int eventType, shared_ptr<EventPoolInterface> pool) {
    while ((int)pools_.size() <= eventType)
        pools_.push_back(shared_ptr<EventPoolInterface>());
    assert(!pools_[eventType].get());
    pools_[eventType] = pool;
}

Event *EventQueueCore::ScheduleEvent(int eventType) {
    assert((eventType >= 0) && (eventType < (int)pools_.size()) && pools_[eventType].get());
    Event *event = pools_[eventType]->Get();
    event->SetType(eventType);
    queues_[schedulingQueue_].push_back(event);
    return event;
}

void EventQueueCore::ProcessEvents() {
    //Log(this).Stream() << "event queues: " << (int)queues_[0].size() << " "
    //                   << (int)queues_[1].size() << endl;
    deque<Event *> *processingQueue = &queues_[schedulingQueue_];
    schedulingQueue_ = 1 - schedulingQueue_;
    while (processingQueue->size()) {
        Event *event = processingQueue->front();
        //Log(this).Stream() << "processing event, type=" << event->Type()
        //                   << ", rtti_type=" << typeid(*event).name() << endl;
        pools_[event->Type()]->Put(event);
        processingQueue->pop_front();
    }
}

}    // Namespace Game.
}    // Namespace kxm.

