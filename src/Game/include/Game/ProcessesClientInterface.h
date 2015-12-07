#ifndef KXM_GAME_PROCESSESCLIENTINTERFACE_H_
#define KXM_GAME_PROCESSESCLIENTINTERFACE_H_


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Game {

class ProcessInterface;
class ProcessOwnerInterface;

//! Reduced interface to the processes mechanism, intended to be handed out to client sub systems.
/*!
 *  \ingroup Game
 */
class ProcessesClientInterface : public virtual Core::Interface {
  public:
    //! Registers the given process as well as its owner, both as weak references.
    virtual void RegisterProcess(ProcessInterface *process, ProcessOwnerInterface *owner) = 0;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_PROCESSESCLIENTINTERFACE_H_