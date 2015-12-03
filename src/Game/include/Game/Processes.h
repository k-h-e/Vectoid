//
//  Processes.h
//  kxm
//
//  Created by Kai Hergenröther on 11/30/12.
//
//


#ifndef KXM_GAME_PROCESSES_H_
#define KXM_GAME_PROCESSES_H_


#include <kxm/Core/ReusableItems.h>


namespace kxm {
namespace Game {

//! Orchestrates a set of processes (i.e. instances of \ref ProcessInterface) into a cooperative
//! multitasking scheme.
/*!
 *  \ingroup Game
 */
class Processes {
  public:
    Processes();
    
    //! Executes the registered processes, and then unregisters those that have indicated that they
    //! are done.
    void ExecuteProcesses();
    //! Returns the number of registered processes.
    int Count();
    
  private:
    struct ProcessInfo {
    };
  
    Processes(const Processes &other);
    Processes &operator=(const Processes &other);
    
    kxm::Core::ReusableItems<ProcessInfo> processes_;
    int                                   numProcesses_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_PROCESSES_H_
