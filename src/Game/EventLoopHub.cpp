//
//  EventLoopHub.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//

#include <Game/EventLoopHub.h>

#include <cassert>
#include <kxm/Core/Buffer.h>

using namespace std;
using namespace kxm::Core;

namespace kxm {
namespace Game {

EventLoopHub::EventLoopHub() {
    shared_.shutdownRequested = false;
}

int EventLoopHub::AddEventLoop() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    
    auto id = (int)shared_.loops.size();
    shared_.loops.push_back(LoopInfo());
    return id;
}    // ... critical section, end.

void EventLoopHub::ScheduleEvents(const unique_ptr<Buffer> &buffer) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    
    Buffer *toHub = buffer.get();
    for (auto &loopInfo : shared_.loops) {
        loopInfo.buffer->Append(toHub->Data(), toHub->DataSize());    // Ok, if data size is 0.
    }
    
    // Wake waiting loop threads for which events are present...
    for (auto &loopInfo : shared_.loops) {
        if (loopInfo.waiting && loopInfo.buffer->DataSize()) {
            loopInfo.stateChanged->notify_all();
        }
    }
}    // ... critical section, end.

bool EventLoopHub::GetEvents(int clientLoopId, std::unique_ptr<Core::Buffer> *buffer) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    
    LoopInfo *info = &shared_.loops[clientLoopId];
    if (!info->buffer->DataSize() && !shared_.shutdownRequested) {
        info->waiting = true;
        do {
            info->stateChanged->wait(critical);
            info = &shared_.loops[clientLoopId];    // Vector could have re-allocated its storage.
        } while (!info->buffer->DataSize() && !shared_.shutdownRequested);
        info->waiting = false;
    }
    
    if (shared_.shutdownRequested) {
        return false;
    }
    
    (*buffer)->Clear();
    info->buffer.swap(*buffer);
    return true;
}    // ... critical section, end.

void EventLoopHub::RequestShutdown() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    shared_.shutdownRequested = true;
    for (auto &loopInfo : shared_.loops) {
        loopInfo.stateChanged->notify_all();
    }
}    // ... critical section, end.
 
}    // Namespace Game.
}    // Namespace kxm.
