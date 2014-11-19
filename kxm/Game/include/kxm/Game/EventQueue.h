//
//  EventQueue.h
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#ifndef KXM_GAME_EVENTQUEUE_H_
#define KXM_GAME_EVENTQUEUE_H_


#include <vector>
#include <memory>
#include <unordered_map>

#include <kxm/Game/Event.h>
#include <kxm/Game/EventHandlerInterface.h>
#include <kxm/Game/EventQueueHub.h>

namespace kxm {

namespace Core {
    class Buffer;
}

namespace Game {

class Event;
class EventQueueHub;

//! Event queue mechanism.
/*!
 *  Internally, there are in fact two queues: the active queue and the schedule queue. New events
 *  get enqueued on the schedule queue using \ref Schedule(), and processing happens on the active
 *  queue using \ref ProcessEvents(). Before calling \ref ProcessEvents(), the events in the
 *  schedule queue will have to be moved to the active queue, for example by calling
 *  \ref SyncWithHub().
 */
class EventQueue {
  public:
    EventQueue(int initialBufferSize);
    EventQueue(const EventQueue &other)             = delete;
    EventQueue &operator=(const EventQueue &other)  = delete;
    EventQueue(const EventQueue &&other)            = delete;
    EventQueue &operator=(const EventQueue &&other) = delete;
    //! Registers the specified event.
    void RegisterEvent(std::unique_ptr<Event> protoType);
    //! Adds a handler for the specified event.
    void AddHandler(const Event::EventType &eventType,
                    const std::shared_ptr<EventHandlerInterface> &handler);
    //! Enqueues the specified event on the schedule queue.
    /*!
     *  The event data gets copied, the client is free to dispose of the event object afterwards.
     */
    void Schedule(const Event &event);
    //! Processes all events from the active queue.
    /*!
     *  As a result of processing the events in the active queue, new events will get scheduled on
     *  the schedule queue via \ref Schedule().
     *
     *  When the method returns, the active queue will be empty.
     */
    void ProcessEvents();
    //! Syncs with the specified \ref EventQueueHub, activating the scheduled events in the process.
    void SyncWithHub(EventQueueHub *hub, EventQueueHub::ClientId clientId);
    
  private:
    struct EventInfo {
        std::unique_ptr<Event>                              prototype;
        std::vector<std::shared_ptr<EventHandlerInterface>> handlers;
        EventInfo(std::unique_ptr<Event> proto) : prototype(std::move(proto)) {}
    };
    
    std::vector<EventInfo>          events_;
    std::unordered_map<size_t, int> idToSlotMap_;
    Core::Buffer                    activeQueue_;
    std::unique_ptr<Core::Buffer>   scheduleQueue_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_EVENTQUEUE_H_
