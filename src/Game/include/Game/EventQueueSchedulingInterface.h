#ifndef KXM_GAME_EVENTQUEUESCHEDULINGINTERFACE_H_
#define KXM_GAME_EVENTQUEUESCHEDULINGINTERFACE_H_


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Game {

class Event;

//! Reduced interface to the event queue mechanism, exclusively allowing for scheduling of new
//! events.
/*!
 *  \ingroup Game
 */
class EventQueueSchedulingInterface : public virtual Core::Interface {
  public:
    //! Enqueues the specified event on the schedule queue.
    /*!
     *  The event data gets copied, the client is free to dispose of the event object afterwards.
     */
    virtual void Schedule(const Event &event) = 0;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTQUEUESCHEDULINGINTERFACE_H_
