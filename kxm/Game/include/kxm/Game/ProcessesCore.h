//
//  ProcessesCore.h
//  kxm
//
//  Created by Kai Hergenröther on 12/1/12.
//
//


#ifndef KXM_GAME_PROCESSESCORE_H_
#define KXM_GAME_PROCESSESCORE_H_


#include <vector>

#include <boost/shared_ptr.hpp>

#include <kxm/Game/Process.h>


namespace kxm {
namespace Game {

class ProcessPoolInterface;

//! Manages a set of processes, i.e. instances of \ref ProcessInterface.
/*!
 *  \ingroup Game
 *
 *  Process objects can either be taken from re-use pool or be individually <c>new</c>ed, see the
 *  different versions of \ref AddProcess().
 *
 *  The core mechanism uses non-negative integers to identify (pooled) process types.
 *  \ref Processes<T> then provides a thin wrapper template so clients can use custom enum types
 *  instead.
 */
class ProcessesCore {
  public:
    ProcessesCore();
    ~ProcessesCore();
    //! Registers another pooled process type with the event queue, together with the process pool
    //! that will be managing the process objects for that process type.
    void RegisterProcessType(int processType, boost::shared_ptr<ProcessPoolInterface> pool);
    //! Adds a new pooled process of the specified type to the process group and grants access to
    //! it, so that the client can configure it before the next call to \ref ExecuteProcesses().
    /*!
     *  The process object is taken from the pool registered for the specified process type. When it
     *  has finished executing, as it can indicate via the return value of
     *  \ref ProcessInterface::Execute(), the \ref Processes mechanism automatically puts it back
     *  into the respective pool.
     */
    Process *AddProcess(int processType);
    //! Adds the specified process, transferring ownership to the \ref Processes object.
    /*!
     *  The process object must have been <c>new</c>ed by the client.  When it has finished
     *  executing, as it can indicate via the return value of \ref ProcessInterface::Execute(), it
     *  will get <c>deleted</c>.
     */
    void AddProcess(Process *process);
    //! Executes all processes and deregisters all processes that indicate that they have finished.
    /*!
     *  Pooled processes that have finished are returned to their respective pool, the others (i.e.
     *  not pooled) get <c>deleted</c>.
     */
    void ExecuteProcesses();
    //! Tells the current number of processes in the group.
    int Count();

  private:
    ProcessesCore(const ProcessesCore &other);
    ProcessesCore &operator=(const ProcessesCore &other);
    void Add(Process *process);
    void Remove(Process *process);
    
    std::vector<boost::shared_ptr<ProcessPoolInterface> > pools_;    // Even faster than a hash map.
    Process                                               anchorProcess_;
    int                                                   numProcesses_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_PROCESSESCORE_H_

