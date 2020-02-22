#ifndef KXM_GAME_EVENTRECEIVERINTERFACE_H_
#define KXM_GAME_EVENTRECEIVERINTERFACE_H_

#include <kxm/Core/Interface.h>

namespace kxm {
namespace Game {

class Event;

//! Interface to event receivers.
/*!
 *  \ingroup Game
 */
class EventReceiverInterface : public virtual Core::Interface {
  public:
    //! Posts the specified event to the receiver.
    virtual void Post(const Event &event) = 0;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENTRECEIVERINTERFACE_H_
