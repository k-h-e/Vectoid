//
//  EventQueueCore.h
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//


#ifndef KXM_GAME_EVENTQUEUECORE_H_
#define KXM_GAME_EVENTQUEUECORE_H_


#include <vector>

#include <boost/shared_ptr.hpp>


namespace kxm {
namespace Game {

class EventPool;

//! Event queue mechanism.
/*!
 *  \ingroup Game
 */
class EventQueueCore {
  public:
    //! Registers another event type with the event queue, together with an event pool that will
    //! be managing the event objects for that event type.
    void RegisterEventType(int eventType, boost::shared_ptr<EventPool> pool);
    
  private:
    std::vector<EventPool> eventPools_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTQUEUECORE_H_

