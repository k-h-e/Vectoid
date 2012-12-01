//
//  ProcessPoolInterface.h
//  kxm
//
//  Created by Kai Hergenröther on 11/30/12.
//
//


#ifndef KXM_GAME_PROCESSPOOLINTERFACE_H_
#define KXM_GAME_PROCESSPOOLINTERFACE_H_


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Game {

class Process;

//! Allows that process pool instances for different process types can be used with the
//! \ref Processes mechanism.
/*!
 *  \ingroup Game
 */
class ProcessPoolInterface : public virtual Core::Interface {
  public:
    virtual Process *Get() = 0;
    virtual void Put(Process *process) = 0;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_PROCESSPOOLINTERFACE_H_
