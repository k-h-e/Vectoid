#ifndef KXM_GAME_PROCESSINTERFACE_H_
#define KXM_GAME_PROCESSINTERFACE_H_


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Game {

//! Interface to processes.
/*!
 *  A process is an ongoing activity that periodically gets called, e.g. once for each frame. It
 *  takes part in a co-operative scheduling scheme managed by \ref Processes.
 *
 *  \ingroup Game
 */
class ProcessInterface : public virtual Core::Interface {
  public:
    //! Executes the process until it co-operatively yields (by returning).
    virtual void Execute() = 0;
    //! Tells whether or not the process has permanently finished.
    virtual bool Finished() = 0;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_PROCESSINTERFACE_H_