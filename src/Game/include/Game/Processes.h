//
//  Processes.h
//  kxm
//
//  Created by Kai Hergenröther on 11/30/12.
//
//

#ifndef KXM_GAME_PROCESSES_H_
#define KXM_GAME_PROCESSES_H_

#include <vector>

#include <kxm/Core/Interface.h>
#include <kxm/Core/ReusableItems.h>

namespace kxm {
namespace Game {

class ProcessInterface;
class ProcessOwnerInterface;

//! Orchestrates a set of processes (i.e. instances of \ref ProcessInterface) into a cooperative
//! multitasking scheme.
/*!
 *  \ingroup Game
 */
class Processes : public virtual Core::Interface {
  public:
    Processes();
    //! Executes the registered processes, and then unregisters those that have indicated that they
    //! are done.
    /*!
     *  Only when this method is executing will get processes or their owners get called.
     *
     *  While executing the registered processes, the processes object is prepared to get all
     *  methods called that it exposes via the ProcessesClientInterface. All other public methods on
     *  the other hand must not get called while ExecuteProcesses() executes.
     */
    void ExecuteProcesses();
    //! Returns the number of registered processes.
    int Count();
    //! Unregisters all processes registered for the specified process owner.
    void UnregisterProcesses(ProcessOwnerInterface *owner);
    
    void RegisterProcess(ProcessInterface *process, ProcessOwnerInterface *owner);
    
  private:
    struct ProcessInfo {
        ProcessInterface      *process;
        ProcessOwnerInterface *owner;
        ProcessInfo(ProcessInterface *aProcess, ProcessOwnerInterface *anOwner)
            : process(aProcess),
              owner(anOwner) {}
        ProcessInfo()
            : process(nullptr),
              owner(nullptr) {}
        // Default-copyable.
    };
  
    Processes(const Processes &other);
    Processes &operator=(const Processes &other);
    
    void DoRegisterProcess(const ProcessInfo &info);
    
    kxm::Core::ReusableItems<ProcessInfo> processes_;
    int                                   numProcesses_;
    bool                                  executingProcesses_;
    std::vector<ProcessInfo>              processesToRegister_;
    std::vector<int>                      toUnregister_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_PROCESSES_H_
