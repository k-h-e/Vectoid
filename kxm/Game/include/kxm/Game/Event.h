//
//  Event.h
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#ifndef KXM_GAME_EVENT_H_
#define KXM_GAME_EVENT_H_


#include <kxm/Core/Interface.h>
#include <kxm/Core/Buffer.h>


namespace kxm {
namespace Game {

//! Base class to game events.
/*!
 *  \ingroup Game
 *
 *  Events exclusively contain "data" fields and never directly reference any other objects. If the
 *  data describes aspects of an actor, the actor is identified via a non-negative integer actor id.
 */
class Event : public virtual Core::Interface {
  public:
    //! Threadsafe.
    class EventType {
      public:
        //! Pass a verbose name used to initially compute a hash value. Only pass C-style string
        //! literals (must live forever and be safely accessible by multiple threads).
        EventType(const char *aName);
            // Copyable, movable.
        const char   *name;
        const size_t id;
    };
    
    //! Returns the type of the event.
    virtual const EventType &Type() = 0;
    //! Writes a binary state representation to the specified target buffer.
    virtual void Serialize(Core::Buffer *targetBuffer) = 0;
    //! Reads from the specified buffer a binary event data representation as produced by
    //! \ref Serialize() and updates the object state accordingly.
    /*!
     *  This fast method expects valid data to be present at the current buffer read position. If
     *  this is not the case, the resulting event state will be undefined.
     */
    virtual void Deserialize(Core::Buffer::Reader *bufferReader) = 0;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_EVENT_H_