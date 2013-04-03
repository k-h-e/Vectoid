//
//  Thread.cpp
//  kxm
//
//  Created by Kai Hergenröther on 3/31/13.
//
//


#include <kxm/Core/Thread.h>

#include <kxm/Core/ThreadingFactoryInterface.h>
#include <kxm/Core/ThreadControlInterface.h>

using namespace boost;


namespace kxm {
namespace Core {

Thread::Thread(const shared_ptr<ActionInterface> &action,
               const ThreadingFactoryInterface &threadingFactory)
        : action_(action) {
    shared_ptr<ThreadControlInterface>(threadingFactory.CreateThread()).swap(threadControl_);
    threadControl_->Spawn(action_.get());
}

Thread::~Thread() {
    threadControl_->Join();
}

}    // Namespace Core.
}    // Namespace kxm.
