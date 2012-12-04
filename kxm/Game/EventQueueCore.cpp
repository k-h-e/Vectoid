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
#include <kxm/Game/EventHandlerInterface.h>

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
            pools_[event->type_]->Put(event);
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

void EventQueueCore::RegisterEventHandler(int eventType, EventHandlerInterface *eventHandler) {
    assert((eventType >= 0) && (eventType < (int)pools_.size()) && pools_[eventType].get());
    while ((int)handlers_.size() <= eventType)
        handlers_.push_back(vector<EventHandlerInterface *>());
    handlers_[eventType].push_back(eventHandler);
}

Event *EventQueueCore::ScheduleEvent(int eventType) {
    assert((eventType >= 0) && (eventType < (int)pools_.size()) && pools_[eventType].get());
    Event *event = pools_[eventType]->Get();
    event->type_ = eventType;
    queues_[schedulingQueue_].push_back(event);
    return event;
}

void EventQueueCore::ProcessEvents() {
    //Log(this).Stream() << "event queues: " << (int)queues_[0].size() << " "
    //                   << (int)queues_[1].size() << endl;
    deque<Event *> *processingQueue = &queues_[schedulingQueue_];
    schedulingQueue_ = 1 - schedulingQueue_;
    int num = 0;
    while (processingQueue->size()) {
        ++num;
        Event *event = processingQueue->front();
        processingQueue->pop_front();
        //Log(this).Stream() << "processing event, type=" << event->Type()
        //                   << ", rtti_type=" << typeid(*event).name() << endl;
        vector<EventHandlerInterface *>::iterator endIter = handlers_[event->type_].end();
        for (vector<EventHandlerInterface *>::iterator iter = handlers_[event->type_].begin();
             iter != endIter; ++iter)
            (*iter)->HandleEvent(event);
        pools_[event->type_]->Put(event);
    }
    //Log().Stream() << "handled " << num << " events" << endl;
}

}    // Namespace Game.
}    // Namespace kxm.

