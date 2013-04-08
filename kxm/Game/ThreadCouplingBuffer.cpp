//
//  ThreadCouplingBuffer.cpp
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#include <kxm/Game/ThreadCouplingBuffer.h>

#include <kxm/Core/LockInterface.h>
#include <kxm/Core/ConditionVariableInterface.h>
#include <kxm/Core/ThreadingFactoryInterface.h>

using namespace boost;
using namespace kxm::Core;


namespace kxm {
namespace Game {

ThreadCouplingBuffer::ThreadCouplingBuffer(const ThreadingFactoryInterface &threadingFactory) {
    lock_ = shared_ptr<LockInterface>(threadingFactory.CreateLock());
    lockProtected_.stateChanged = shared_ptr<ConditionVariableInterface>(
                                      threadingFactory.CreateConditionVariable(lock_.get()));
    lockProtected_.seqNos[0]    = 0;
    lockProtected_.seqNos[1]    = 0;
    lockProtected_.numAccessors = 0;
}

ThreadCouplingBuffer::Accessor ThreadCouplingBuffer::Access(int sendDirection) {
    assert((sendDirection >= 0) && (sendDirection <= 1));
    lock_->Lock();
    ++lockProtected_.numAccessors;
    return Accessor(this, sendDirection);
}

void ThreadCouplingBuffer::SignOffAccessor() {
    --lockProtected_.numAccessors;
    if (!lockProtected_.numAccessors)
        lock_->Unlock();
}

ThreadCouplingBuffer::Accessor::Accessor(ThreadCouplingBuffer *buffer, int sendDirection)
        : buffer_(buffer),
          sendDirection_(sendDirection) {
}

ThreadCouplingBuffer::Accessor::Accessor(const Accessor &other) {
    *this = other;
}

ThreadCouplingBuffer::Accessor::~Accessor() {
    buffer_->SignOffAccessor();
}

ThreadCouplingBuffer::Accessor &ThreadCouplingBuffer::Accessor::operator=(const Accessor &other) {
    buffer_        = other.buffer_;
    sendDirection_ = other.sendDirection_;
    ++(buffer_->lockProtected_.numAccessors);    // We exist, so the lock is held.
    return *this;
}

Core::Buffer &ThreadCouplingBuffer::Accessor::SendBuffer() {
    return buffer_->lockProtected_.buffers[sendDirection_];    // We exist, so the lock is held.
}

Core::Buffer &ThreadCouplingBuffer::Accessor::ReceiveBuffer() {
    return buffer_->lockProtected_.buffers[1 - sendDirection_];    // We exist, so the lock is held.
}

void ThreadCouplingBuffer::Accessor::SignalUpdateForSendDirection() {
    ++(buffer_->lockProtected_.seqNos[sendDirection_]);    // We exist, so the lock is held.
    buffer_->lockProtected_.stateChanged->SignalAll();
}

uint32_t ThreadCouplingBuffer::Accessor::SeqNoForReceiveDirection() {
    return buffer_->lockProtected_.seqNos[1 - sendDirection_];    // We exist, so the lock is held.
}

}    // Namespace Game.
}    // Namespace kxm.

