//
//  EventQueueHub.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#include <Game/EventQueueHub.h>

#include <cassert>
#include <kxm/Core/Buffer.h>

using namespace std;
using namespace kxm::Core;


namespace kxm {
namespace Game {

EventQueueHub::EventQueueHub() {
    shared_.seqNo             = 0;
    shared_.shutdownRequested = false;
}

int EventQueueHub::AddClient() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    
    auto id = (int)shared_.buffers.size();
    shared_.buffers.push_back(unique_ptr<Buffer>(new Buffer(initialBufferSize)));
    return id;
}    // ... critical section, end.

bool EventQueueHub::Sync(int id, unique_ptr<Buffer> *buffer, int *inOutWaitSeqNo) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    
    if (inOutWaitSeqNo) {
        while (   (shared_.seqNo == *inOutWaitSeqNo)
               && !shared_.shutdownRequested) {
            shared_.stateChanged.wait(critical);
        }
        *inOutWaitSeqNo = shared_.seqNo;
    }
    
    Buffer *toHub = (*buffer).get();
    for (int i = 0; i < (int)shared_.buffers.size(); ++i) {
        shared_.buffers[i]->Append(toHub->Data(), toHub->DataSize());    // Ok, if data size is 0.
    }
    
    toHub->Clear();
    shared_.buffers[id].swap(*buffer);
    
    if (!inOutWaitSeqNo) {
        ++shared_.seqNo;
        if (shared_.seqNo < 0) {
            shared_.seqNo = 0;
        }
        shared_.stateChanged.notify_all();
    }
    
    return !shared_.shutdownRequested;
}    // ... critical section, end.

void EventQueueHub::RequestShutdown() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    shared_.shutdownRequested = true;
    shared_.stateChanged.notify_all();
}    // ... critical section, end.

}    // Namespace Game.
}    // Namespace kxm.
