//
//  EventQueueHub.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#include <kxm/Game/EventQueueHub.h>

#include <cassert>
#include <kxm/Core/Buffer.h>

using namespace std;
using namespace kxm::Core;


namespace kxm {
namespace Game {

EventQueueHub::EventQueueHub() {
    shared_.nextId     = 1;
    shared_.toReadMask = 0;
}

EventQueueHub::ClientId EventQueueHub::GetUniqueClientId() {
    lock_guard<mutex> critical(lock_);    // Critical section...
    
    assert(shared_.nextId < (unsigned int)256);
    unsigned int id = shared_.nextId;
    shared_.toReadMask  |= id;
    shared_.nextId     <<= 1;
    return id;
}    // ... critical section, end.

void EventQueueHub::Sync(ClientId id, unique_ptr<Buffer> *toHubBuffer, Buffer *toQueueBuffer,
                         bool wait) {
    lock_guard<mutex> critical(lock_);    // Critical section...
    
    // Append to-hub-buffer to active buffer queue...
    shared_.activeBuffers.push_back(BufferInfo(std::move(*toHubBuffer), shared_.toReadMask));
    
    // Provide client with replacement buffer...
    unique_ptr<Buffer> newBuffer;
    if (shared_.bufferPool.size()) {
        newBuffer = std::move(shared_.bufferPool.front());
        shared_.bufferPool.pop();
            // Buffers get cleared as they are added to the pool.
    }
    else {
        newBuffer = unique_ptr<Buffer>(new Buffer(128));
        newBuffer->Clear();
    }
    *toHubBuffer = std::move(newBuffer);
    
    // Copy to-queue event data...
    toQueueBuffer->Clear();
    for (auto info = shared_.activeBuffers.begin(); info != shared_.activeBuffers.end(); ++info) {
        if (info->unreadBits & id) {
            int size = info->buffer->DataSize();
            if (size)
                toQueueBuffer->Append(info->buffer->Data(), size);
            info->unreadBits &= ~id;
        }
    }
    
    // Remove no longer needed active buffers and add them to the pool...
    while (shared_.activeBuffers.size()) {
        BufferInfo &info = shared_.activeBuffers.front();
        if (info.unreadBits)
            break;
        info.buffer->Clear();
        shared_.bufferPool.push(std::move(info.buffer));
    }
}    // ... critical section, end.

EventQueueHub::BufferInfo::BufferInfo(std::unique_ptr<Core::Buffer> &&aBuffer,
                                      unsigned int someUnreadBits)
        : buffer(std::move(aBuffer)),
          unreadBits(someUnreadBits) {
}

}    // Namespace Game.
}    // Namespace kxm.
