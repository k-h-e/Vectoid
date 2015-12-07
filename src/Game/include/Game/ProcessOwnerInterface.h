#ifndef KXM_GAME_PROCESSOWNERINTERFACE_H_
#define KXM_GAME_PROCESSOWNERINTERFACE_H_

#include <kxm/Core/Interface.h>


namespace kxm {
namespace Game {

class ProcessInterface;

//! Interface to entities owning processes.
/*!
 *  \ingroup Game
 */
class ProcessOwnerInterface : public virtual Core::Interface {
  public:
    //! Informs the process owner that a process has finished executing.
    virtual void HandleProcessFinished(ProcessInterface *process) = 0;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_PROCESSOWNERINTERFACE_H_