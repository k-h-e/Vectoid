//
//  EventQueue.cpp
//  kxm
//
//  Created by Kai Hergenröther on 10/7/12.
//
//


#include <kxm/Game/EventQueueCore.h>

#include <kxm/Core/logging.h>
#include <kxm/Core/exceptions.h>

using namespace std;
using namespace kxm::Core;


namespace kxm {
namespace Game {

EventQueueCore::EventQueueCore(int numEventTypes) {
    queues_[0] = events_.AddGroup();
    queues_[1] = events_.AddGroup();
    for (int i = 0; i < numEventTypes; ++i)
        eventTypes_.push_back(EventTypeInfo(ActorEvent));
    if (!eventTypes_.size())
        Log(this).Stream() << "no event types registered!" << endl;
}

void EventQueueCore::SetEventDataType(int eventType, EventDataType dataType) {
    if ((eventType < 0) || (eventType >= (int)eventTypes_.size()))
        throw BadArgumentException();
    EventTypeInfo &info = eventTypes_[eventType];
    if (info.handlers.size())
        throw OperationUnavailableException();
    info.dataType = dataType;
}

void EventQueueCore::AddHandler(int eventType, boost::shared_ptr<EventHandlerInterface> handler) {
    if ((eventType < 0) || (eventType >= (int)eventTypes_.size()))
        throw BadArgumentException();
    EventTypeInfo &info = eventTypes_[eventType];
    bool handlerMatches;
    switch (info.dataType) {
        case VectorEvent:
            handlerMatches = (dynamic_cast<VectorEventHandlerInterface *>(handler.get()) != 0);
            break;
        case TransformEvent:
            handlerMatches = (dynamic_cast<TransformEventHandlerInterface *>(handler.get()) != 0);
            break;
        case ActorEvent:
        default:
            handlerMatches = (dynamic_cast<ActorEventHandlerInterface *>(handler.get()) != 0);
            break;
    }
    if (!handlerMatches)
        throw OperationUnavailableException();
    info.handlers.push_back(handler);
}

EventQueueCore::EventTypeInfo::EventTypeInfo(EventDataType eventDataType) {
    dataType = eventDataType;
}

}    // Namespace Game.
}    // Namespace kxm.
