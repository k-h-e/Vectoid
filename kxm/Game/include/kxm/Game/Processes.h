//
//  Processes.h
//  kxm
//
//  Created by Kai Hergenröther on 11/30/12.
//
//


#ifndef KXM_GAME_PROCESSES_H_
#define KXM_GAME_PROCESSES_H_


#include <kxm/Game/ProcessesCore.h>


namespace kxm {
namespace Game {

//! Manages a set of processes, i.e. instances of \ref ProcessInterface. Wraps \ref ProcessesCore to
//! allow clients to use custom enums to specify (pooled) process types, instead of <c>int</c>s.
/*!
 *  \ingroup Game
 */
template<class T>
class Processes : private ProcessesCore {
  public:
    //! Adds the specified process, transferring ownership to the \ref Processes object.
    /*!
     *  The process object must have been <c>new</c>ed by the client.  When it has finished
     *  executing, as it can indicate via the return value of \ref ProcessInterface::Execute(), it
     *  will get <c>deleted</c>.
     *
     *  May be called from processes managed by this process group.
     */
    void AddProcess(Process *process) { ProcessesCore::AddProcess(process); }
    //! Executes all processes and deregisters all processes that indicate that they have finished.
    /*!
     *  Pooled processes that have finished are returned to their respective pool, the others (i.e.
     *  not pooled) get <c>deleted</c>.
     */
    void ExecuteProcesses(const Process::Context &context) {
        ProcessesCore::ExecuteProcesses(context);
    }
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_PROCESSES_H_
