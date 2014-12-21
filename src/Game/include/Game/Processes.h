//
//  Processes.h
//  kxm
//
//  Created by Kai Hergenröther on 11/30/12.
//
//


#ifndef KXM_GAME_PROCESSES_H_
#define KXM_GAME_PROCESSES_H_


#include <Game/ProcessesCore.h>


namespace kxm {
namespace Game {

//! Orchestrates a set of processes (i.e. instances of \ref Process) into a cooperative multitasking
//! scheme. Wraps \ref ProcessesCore to allow clients to use custom enums to specify (pooled)
//! process types, instead of <c>int</c>s.
/*!
 *  \ingroup Game
 */
template<class T>
class Processes : private ProcessesCore {
  public:
    Processes() {}
  
    //! See \ref ProcessesCore::RegisterProcessType().
    void RegisterProcessType(T processType, std::shared_ptr<PoolInterface<Process>> pool) {
        ProcessesCore::RegisterProcessType((int)processType, pool);
    }
    
    //! See \ref ProcessesCore::AddProcess(int).
    Process &AddProcess(T processType) {
        return ProcessesCore::AddProcess((int)processType);
    }
    
    //! See \ref ProcessesCore::AddProcess(const boost::shared_ptr<Process> &).
    void AddProcess(const std::shared_ptr<Process> &process) {
        ProcessesCore::AddProcess(process);
    }
    
    //! See \ref ProcessesCore::ExecuteProcesses().
    void ExecuteProcesses(const ExecutionContext &context) {
        ProcessesCore::ExecuteProcesses(context);
    }
    
    //! See \ref ProcessesCore::Count().
    int Count() {
        return ProcessesCore::Count();
    }
    
  private:
    Processes(const Processes &other);
    Processes &operator=(const Processes &other);
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_PROCESSES_H_
