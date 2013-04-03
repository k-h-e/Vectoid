//
//  ThreadCouplingBuffer.cpp
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#include <kxm/Game/ThreadCouplingBuffer.h>


namespace kxm {
namespace Game {

ThreadCouplingBuffer::ThreadCouplingBuffer()
    : numAccessors_(0) {
}

ThreadCouplingBuffer::Accessor ThreadCouplingBuffer::Access() {
    // Lock!
    ++numAccessors_;
    return Accessor(this);
}

void ThreadCouplingBuffer::SignOffAccessor() {
    --numAccessors_;
    if (!numAccessors_) {
        // Unlock!
    }
}

ThreadCouplingBuffer::Accessor::Accessor(ThreadCouplingBuffer *buffer)
        : buffer_(buffer) {
}

ThreadCouplingBuffer::Accessor::Accessor(const Accessor &other) {
    *this = other;
}

ThreadCouplingBuffer::Accessor::~Accessor() {
    buffer_->SignOffAccessor();
}

ThreadCouplingBuffer::Accessor &ThreadCouplingBuffer::Accessor::operator=(const Accessor &other) {
    buffer_ = other.buffer_;
    ++(buffer_->numAccessors_);
    return *this;
}

Core::Buffer &ThreadCouplingBuffer::Accessor::BufferForDirection(int direction) {
    return buffer_->buffers_[direction];
}

}    // Namespace Game.
}    // Namespace kxm.

