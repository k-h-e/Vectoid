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

namespace kxm {

namespace Core {
    class Buffer;
}

namespace Game {

class Event;

//! Event queue mechanism.
class EventQueue {
  public:
    EventQueue();
    EventQueue(const EventQueue &other)             = delete;
    EventQueue &operator=(const EventQueue &other)  = delete;
    EventQueue(const EventQueue &&other)            = delete;
    EventQueue &operator=(const EventQueue &&other) = delete;
    //! Registers the specified event.
    void RegisterEvent(std::unique_ptr<Event> protoType);
    //! Adds a handler for the specified event.
    void AddHandler(const Event::EventType &eventType,
                    const std::shared_ptr<EventHandlerInterface> &handler);
    
  private:
    struct EventInfo {
        std::unique_ptr<Event>                              prototype;
        std::vector<std::shared_ptr<EventHandlerInterface>> handlers;
        EventInfo(std::unique_ptr<Event> proto) : prototype(std::move(proto)) {}
    };
    
    std::vector<EventInfo>          events_;
    std::unordered_map<size_t, int> idToSlotMap_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_EVENTQUEUE_H_
