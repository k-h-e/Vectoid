//
//  ProcessesCore.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/1/12.
//
//


#include <kxm/Game/ProcessesCore.h>

#include <kxm/Core/logging.h>
#include <kxm/Game/CustomProcessPool.h>

using namespace std;
using namespace boost;
using namespace kxm::Core;


namespace kxm {
namespace Game {

ProcessesCore::ProcessesCore()
        : processes_(2),
          numProcesses_(0) {
    pools_.push_back(shared_ptr<PoolInterface<Process> >(
        customProcessPool_ = new CustomProcessPool()));
}

void ProcessesCore::RegisterProcessType(int processType,
                                        boost::shared_ptr<PoolInterface<Process> > pool) {
    assert(processType >= 0);
    int slot = processType + 1;    // Slot 0 is for custom process pool.
    while ((int)pools_.size() <= slot)
        pools_.push_back(shared_ptr<PoolInterface<Process> >());
    assert(!pools_[slot].get());
    pools_[slot] = pool;
}

Process &ProcessesCore::AddProcess(int processType) {
    assert (processType >= 0);
    int slot = processType + 1;    // Slot 0 is for custom process pool.
    assert((slot < (int)pools_.size()) && (!pools_[slot].get()));
    int itemId;
    Process &process = pools_[slot]->Get(&itemId);
    processes_.Get(addedProcessesGroup).Set(slot, itemId);
    ++numProcesses_;
    return process;
}

void ProcessesCore::AddProcess(const boost::shared_ptr<Process> &process) {
    int itemId;
    customProcessPool_->Get(process, &itemId);
    processes_.Get(addedProcessesGroup).Set(0, itemId);
    ++numProcesses_;
}

void ProcessesCore::ExecuteProcesses(const Process::Context &context) {
    ReusableItems<ProcessInfo>::Iterator iter = processes_.GetIterator(addedProcessesGroup);
    int num = 0;
    while (iter.Next()) {
        processes_.Move(iter.ItemId(), activeProcessesGroup);
        ++num;
    }
    if (num)
        printf("activated %d processes\n", num);
    
    iter = processes_.GetIterator(activeProcessesGroup);
    num  = 0;
    while (ProcessInfo *info = iter.Next()) {
        if (!(pools_[info->pool]->Access(info->itemId).Execute(context))) {
            pools_[info->pool]->Put(info->itemId);
            processes_.Put(iter.ItemId());
            --numProcesses_;
            ++num;
        }
    }
    if (num)
        printf("deregistered %d processes\n", num);
}

int ProcessesCore::Count() {
    return numProcesses_;
}
    
}    // Namespace Game.
}    // Namespace kxm.
