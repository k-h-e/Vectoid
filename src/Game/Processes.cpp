#include <cassert>
#include <Game/Processes.h>
#include <Game/ProcessInterface.h>
#include <Game/ProcessOwnerInterface.h>

using namespace std;


namespace kxm {
namespace Game {

Processes::Processes()
        : processes_(1),
          numProcesses_(0),
          executingProcesses_(false) {
    // Nop.
}
    
void Processes::ExecuteProcesses() {
    assert(!executingProcesses_);
    executingProcesses_ = true;
    
    auto iterator = processes_.GetIterator(0);
    while (ProcessInfo *info = iterator.Next()) {
        if (!info->process->Finished()) {
            info->process->Execute();
        }
        if (info->process->Finished()) {
            toUnregister_.push_back(iterator.ItemId());
        }
    }
    
    if (!toUnregister_.empty()) {
        for (int id : toUnregister_) {
            ProcessInfo &info = processes_.Item(id);
            info.owner->HandleProcessFinished(info.process);
            processes_.Put(id);
            --numProcesses_;
        }
        toUnregister_.clear();
    }
    
    executingProcesses_ = false;
    
    if (!processesToRegister_.empty()) {
        for (ProcessInfo &info : processesToRegister_) {
            DoRegisterProcess(info);
        }
        processesToRegister_.clear();
    }
}
    
int Processes::Count() {
    assert(!executingProcesses_);
    return numProcesses_;
}

void Processes::UnregisterProcesses(ProcessOwnerInterface *owner) {
    assert(!executingProcesses_);
    auto iterator = processes_.GetIterator(0);
    while (iterator.Next()) {
        toUnregister_.push_back(iterator.ItemId());
    }
    for (int id : toUnregister_) {
        processes_.Put(id);
        --numProcesses_;
    }
    toUnregister_.clear();
}

//! Might get called while executing processes.
void Processes::RegisterProcess(ProcessInterface *process, ProcessOwnerInterface *owner) {
    ProcessInfo info(process, owner);
    if (executingProcesses_) {
        processesToRegister_.push_back(info);
    }
    else {
        DoRegisterProcess(info);
    }
}

void Processes::DoRegisterProcess(const ProcessInfo &info) {
    processes_.Get(0) = info;
    ++numProcesses_;
}

}    // Namespace Game.
}    // Namespace kxm.
