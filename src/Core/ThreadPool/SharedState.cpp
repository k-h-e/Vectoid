#include "SharedState.h"

#include <kxm/Core/logging.h>
#include "Runner.h"
#include "SharedRunnerState.h"

using std::shared_ptr;
using std::make_shared;
using std::mutex;
using std::thread;
using std::unique_lock;
using std::endl;
using kxm::Core::ActionInterface;
using K::Core::CompletionHandlerInterface;
using kxm::Core::Log;

namespace K {
namespace Core {

void ThreadPool::SharedState::Run(const shared_ptr<ActionInterface> &action,
                                  const shared_ptr<CompletionHandlerInterface> &completionHandler) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    int slot;
    if (idleThreads_.size()) {
        slot = *idleThreads_.begin();
        idleThreads_.erase(slot);
    }
    else {
        slot = threads_.size();
        threads_.push_back(ThreadInfo());
        ThreadInfo &info = threads_[slot];
        info.sharedRunnerState = make_shared<SharedRunnerState>();
        info.runner            = make_shared<Runner>(slot, *this, info.sharedRunnerState);
        auto aRunner = info.runner;
        info.thread.reset(new thread([=]{ aRunner->Run(); }));
        Log().Stream() << "spawned thread " << slot << endl;
    }

    Log().Stream() << "dispatching action to thread " << slot << endl;
    ThreadInfo &info = threads_[slot];
    info.sharedRunnerState->Execute(action, completionHandler);
    Log().Stream() << idleThreads_.size() << " threads now idle" << endl;
}    // ... critical section, end.

void ThreadPool::SharedState::OnCompletion(int operationId) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    idleThreads_.insert(operationId);
    stateChanged_.notify_all();
    Log().Stream() << "thread " << operationId << " idle" << endl;
    Log().Stream() << idleThreads_.size() << " threads now idle" << endl;
}    // ... critical section, end.

void ThreadPool::SharedState::ShutDown() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    while (idleThreads_.size() < threads_.size()) {
        stateChanged_.wait(critical);
    }
    for (ThreadInfo &info : threads_) {
        info.sharedRunnerState->RequestShutDown();
    }
    for (ThreadInfo &info : threads_) {
        info.thread->join();
    }
    Log().Stream() << "all pool threads terminated" << endl;
}    // ... critical section, end.

}    // Namespace Core.
}    // Namespace K.
