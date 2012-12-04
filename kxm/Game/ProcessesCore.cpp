//
//  ProcessesCore.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/1/12.
//
//


#include <kxm/Game/ProcessesCore.h>

#include <kxm/Core/logging.h>
#include <kxm/Game/ProcessPoolInterface.h>

using namespace std;
using namespace boost;
using namespace kxm::Core;


namespace kxm {
namespace Game {

ProcessesCore::ProcessesCore()
        : numProcesses_(0) {
    processesAnchor_.next_    = &processesAnchor_;
    processesAnchor_.prev_    = &processesAnchor_;
    newProcessesAnchor_.next_ = &newProcessesAnchor_;
    newProcessesAnchor_.prev_ = &newProcessesAnchor_;
}

ProcessesCore::~ProcessesCore() {
    ActivateNewProcesses();
    while (numProcesses_)
        Remove(processesAnchor_.next_);
}

void ProcessesCore::RegisterProcessType(int processType, shared_ptr<ProcessPoolInterface> pool) {
    while ((int)pools_.size() <= processType)
        pools_.push_back(shared_ptr<ProcessPoolInterface>());
    assert(!pools_[processType].get());
    pools_[processType] = pool;
}

Process *ProcessesCore::AddProcess(int processType) {
    assert((processType >= 0) && (processType < (int)pools_.size()) && pools_[processType].get());
    Process *process = pools_[processType]->Get();
    process->type_ = processType;    // This means it will be put back into its pool when finished.
    Add(process);
    return process;
}

void ProcessesCore::AddProcess(Process *process) {
    process->type_ = -1;    // This means it will get deleted when it is finished.
    Add(process);
}

void ProcessesCore::ExecuteProcesses(const Process::Context &context) {
    ActivateNewProcesses();
    Process *last = &processesAnchor_,
            *current;
    while ((current = last->next_) != &processesAnchor_) {
        if (current->Execute(context))
            last = current;
        else
            Remove(current);
    }
}

int ProcessesCore::Count() {
    return numProcesses_;
}

void ProcessesCore::Add(Process *process) {
    Process *prev = newProcessesAnchor_.prev_;
    prev->next_               = process;
    process->prev_            = prev;
    process->next_            = &newProcessesAnchor_;
    newProcessesAnchor_.prev_ = process;
    ++numProcesses_;
    Log(this).Stream() << "process added, num=" << numProcesses_ << endl;
}

void ProcessesCore::ActivateNewProcesses() {
    if (newProcessesAnchor_.next_ == &newProcessesAnchor_)
        return;    // There are no new processs to activate.
    Process *last     = processesAnchor_.prev_,
            *firstNew = newProcessesAnchor_.next_,
            *lastNew  = newProcessesAnchor_.prev_;
    last->next_            = firstNew;
    firstNew->prev_        = last;
    lastNew->next_         = &processesAnchor_;
    processesAnchor_.prev_ = lastNew;
    
    newProcessesAnchor_.next_ = &newProcessesAnchor_;
    newProcessesAnchor_.prev_ = &newProcessesAnchor_;
    
    Log(this).Stream() << "activated new processes" << endl;
}

void ProcessesCore::Remove(Process *process) {
    Process *prev = process->prev_,
            *next = process->next_;
    prev->next_ = next;
    next->prev_ = prev;
    --numProcesses_;
    
    if (process->type_ == -1) {
        delete process;
        Log(this).Stream() << "process deleted, num=" << numProcesses_ << endl;
    }
    else {
        pools_[process->type_]->Put(process);
        Log(this).Stream() << "process returned to pool, num=" << numProcesses_ << endl;
    }
}

}    // Namespace Game.
}    // Namespace kxm.
