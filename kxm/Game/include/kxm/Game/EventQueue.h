//
//  EventQueue.h
//  kxm
//
//  Created by Kai Hergenröther on 10/8/12.
//
//


#ifndef KXM_GAME_EVENTQUEUE_H_
#define KXM_GAME_EVENTQUEUE_H_


#include <kxm/Game/EventQueueCore.h>


namespace kxm {
namespace Game {

//! Central game event mechanism.
/*!
 *  \ingroup Game
 */
template<class EventTypeT>
class EventQueue : public virtual EventQueueCore {
  public:
    EventQueue(EventTypeT numEventTypes);
    //! Configures the data type for the specified event type. Only works as long as no handler has
    //! been registered for the event type.
    void SetEventDataType(EventTypeT eventType, EventDataType dataType);
    //! Adds a handler for the specified event type. The handler type must match the event data
    //! type set via SetEventDataType().
    void AddHandler(EventTypeT eventType, boost::shared_ptr<EventHandlerInterface> handler);
};

template<class EventTypeT>
EventQueue<EventTypeT>::EventQueue(EventTypeT numEventTypes)
    : EventQueueCore((int)numEventTypes) {
}

template<class EventTypeT>
void EventQueue<EventTypeT>::SetEventDataType(EventTypeT eventType, EventDataType dataType) {
    EventQueueCore::SetEventDataType((int)eventType, dataType);
}

template<class EventTypeT>
void EventQueue<EventTypeT>::AddHandler(EventTypeT eventType,
                                        boost::shared_ptr<EventHandlerInterface> handler) {
    EventQueueCore::SetEventDataType((int)eventType, handler);
}

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTQUEUE_H_
