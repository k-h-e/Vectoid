//
//  Event.h
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//

#ifndef KXM_GAME_OLDEVENT_H_
#define KXM_GAME_OLDEVENT_H_


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
class OldEvent : public virtual Core::Interface {
  public:
    OldEvent() : type_(-1) {}
    //! Writes the integer-valued event type to the specified target binary buffer, followed by a
    //! binary representation of the event data.
    virtual void Serialize(Core::Buffer *targetBuffer) = 0;
    //! Reads from the specified buffer a binary event data representation as produced by
    //! \ref Serialize(), but without the leading integer-valued event type, and sets the receiver's
    //! state accordingly.
    /*!
     *  This fast method expects valid data to be present at the current buffer read position. If
     *  this is not the case, the resulting event state will be undefined. If you also need to
     *  validate the input data, for example if it has been read from the network, use
     *  \ref DeserializeAndValidate() instead.
     */
    virtual void Deserialize(Core::Buffer::Reader *bufferReader) = 0;
    //! Like \ref Deserialize(), but also validates the input data.
    /*!
     *  \return <c>false</c> in case the input data was invalid. In this case the resulting event
     *          state will be undefined, as well as the resulting buffer read position.
     */
    virtual bool DeserializeAndValidate(Core::Buffer::Reader *bufferReader) = 0;
    
  protected:
    int type_;
    
  private:
    friend class OldEventQueueCore;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_OLDEVENT_H_

