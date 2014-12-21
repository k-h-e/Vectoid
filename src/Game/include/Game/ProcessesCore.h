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
#include <memory>

#include <kxm/Core/ReusableItems.h>
#include <Game/Process.h>


namespace kxm {
namespace Game {

template<class T> class PoolInterface;
class CustomProcessPool;

//! Orchestrates a set of processes (i.e. instances of \ref Process) into a cooperative multitasking
//! scheme.
/*!
 *  \ingroup Game
 *
 *  The core mechanism uses non-negative integers to identify (pooled) process types.
 *  \ref Processes<T> then provides a thin wrapper template so clients can use custom enum types
 *  instead.
 */
class ProcessesCore {
  public:
    ProcessesCore();
    //! Registers another pooled process type, together with the process pool that will be managing
    //! the process objects for that process type.
    void RegisterProcessType(int processType, std::shared_ptr<PoolInterface<Process>> pool);
    //! Adds a new pooled process of the specified type and grants access to it, so that the client
    //! can configure it before the next call to \ref ExecuteProcesses().
    /*!
     *  The process object is taken from the pool registered for the specified process type. When it
     *  has finished executing, as it can indicate via the return value of
     *  \ref Process::Execute(), the \ref Processes mechanism automatically puts it back
     *  into the respective pool.
     *
     *  May be called from processes managed by this process group.
     */
    Process &AddProcess(int processType);
    //! Adds the specified custom process.
    /*!
     *  When the process has finished executing, as it can indicate via the return value of
     *  \ref Process::Execute(), the processes mechanism will drop its reference.
     *
     *  May be called from processes managed by this process group.
     */
    void AddProcess(const std::shared_ptr<Process> &process);
    //! Executes all processes and deregisters all processes that indicate that they have finished.
    /*!
     *  Pooled processes that have finished are returned to their respective pools. For custom
     *  processes, the processes mechanism drops the respective references.
     */
    void ExecuteProcesses(const ExecutionContext &context);
    //! Tells the current number of processes.
    int Count();

  private:
    const int activeProcessesGroup = 0,
              addedProcessesGroup  = 1;
    struct ProcessInfo {
        int pool;
        int itemId;
        ProcessInfo() : pool(0), itemId(0) {}
        void Set(int aPool, int anItemId) { pool = aPool;  itemId = anItemId; }
    };
    ProcessesCore(const ProcessesCore &other);
    ProcessesCore &operator=(const ProcessesCore &other);
    
    std::vector<std::shared_ptr<PoolInterface<Process>>>  pools_;
    CustomProcessPool                                     *customProcessPool_;
        // Faster than a hash map, pool in slot 0 will be the custom process pool.
    Core::ReusableItems<ProcessInfo>                      processes_;
    int                                                   numProcesses_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_PROCESSESCORE_H_

