//
//  EventQueue.h
//  kxm
//
//  Created by Kai Hergenröther on 10/7/12.
//
//


#ifndef KXM_GAME_EVENTQUEUECORE_H_
#define KXM_GAME_EVENTQUEUECORE_H_


#include <vector>

#include <boost/shared_ptr.hpp>

#include <kxm/Core/Interface.h>
#include <kxm/Core/ItemGroups.h>
#include <kxm/Vectoid/Vector.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/EventHandlerInterface.h>


namespace kxm {
namespace Game {

//! Non-template core of the central game event mechanism.
/*!
 *  \ingroup Game
 */
class EventQueueCore : public virtual Core::Interface {
  public:
    enum EventDataType { ActorEvent,
                         VectorEvent,
                         TransformEvent };

    //! Creates an event queue mechanism for event types <c>[0, numEventTypes - 1]</c>.
    EventQueueCore(int numEventTypes);
    
    //! Configures the data type for the specified event type. Only works as long as no handler has
    //! been registered for the event type.
    void SetEventDataType(int eventType, EventDataType dataType);
    //! Adds a handler for the specified event type. The handler type must match the event data
    //! type set via SetEventDataType().
    void AddHandler(int eventType, boost::shared_ptr<EventHandlerInterface> handler);
    
  private:
    struct EventTypeInfo {
        EventTypeInfo(EventDataType eventDataType);
        EventDataType                                          dataType;
        std::vector<boost::shared_ptr<EventHandlerInterface> > handlers;
    };
    struct Event {
        int type;
        int dataIndex;
    };
    struct ActorEventData {
        int actor;
    };
    struct VectorEventData {
        int             actor;
        Vectoid::Vector vector;
    };
    struct TransformEventData {
        int                actor;
        Vectoid::Transform transform;
    };
    
    EventQueueCore(const EventQueueCore &other);
    EventQueueCore &operator=(const EventQueueCore &other);
    
    Core::ItemGroups<Event>              events_;
    int                                  queues_[2];
    Core::ItemGroups<ActorEventData>     actorEventData_;
    Core::ItemGroups<VectorEventData>    vectorEventData_;
    Core::ItemGroups<TransformEventData> transformEventData_;
    std::vector<EventTypeInfo>           eventTypes_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_EVENTQUEUECORE_H_

