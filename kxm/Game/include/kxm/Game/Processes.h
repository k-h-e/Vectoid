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
    void AddProcess(Process *process) { ProcessesCore::AddProcess(process); }
    void ExecuteProcesses() { ProcessesCore::ExecuteProcesses(); }

};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_PROCESSES_H_
