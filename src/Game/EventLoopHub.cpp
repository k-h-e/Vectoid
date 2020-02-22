#include <kxm/Game/EventLoopHub.h>

#include <cassert>
#include <cstdio>
#include <kxm/Core/Buffer.h>
#include <kxm/Game/Event.h>

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

bool EventLoopHub::RegisterIdToSlotMapping(size_t id, int slot) {
    unique_lock<mutex> critical(lock_);    // Critical section...

    auto iter = shared_.idToSlotMap.find(id);
    if (iter != shared_.idToSlotMap.end()) {
        if (iter->second == slot) {
            return true;
        }
        else {
            return false;
        }
    }

    shared_.idToSlotMap[id] = slot;
    return true;
}    // ... critical section, end.

void EventLoopHub::Post(const Core::Buffer &buffer) {
    unique_lock<mutex> critical(lock_);    // Critical section...
    DoPost(buffer);
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
 
void EventLoopHub::Post(const Event &event) {
    unique_lock<mutex> critical(lock_);    // Critical section...

    auto iter = shared_.idToSlotMap.find(event.Type().id);
    assert(iter != shared_.idToSlotMap.end());
    int slot = iter->second;
    shared_.eventsToSchedule.Append(&slot, sizeof(slot));
    event.Serialize(&shared_.eventsToSchedule);
    DoPost(shared_.eventsToSchedule);
    shared_.eventsToSchedule.Clear();
}    // ... critical section, end.

// Expects lock to be held.
void EventLoopHub::DoPost(const Core::Buffer &buffer) {
    for (auto &loopInfo : shared_.loops) {
        loopInfo.buffer->Append(buffer.Data(), buffer.DataSize());    // Ok, if data size is 0.
    }

    // Wake waiting loop threads for which events are present...
    for (auto &loopInfo : shared_.loops) {
        if (loopInfo.waiting && loopInfo.buffer->DataSize()) {
            loopInfo.stateChanged->notify_all();
        }
    }
}

}    // Namespace Game.
}    // Namespace kxm.
