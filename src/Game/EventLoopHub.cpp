#include <kxm/Game/EventLoopHub.h>

#include <cassert>
#include <cstdio>
#include <kxm/Core/Buffer.h>
#include <K/Core/Log.h>
#include <kxm/Game/Event.h>

using std::mutex;
using std::unique_lock;
using std::to_string;
using K::Core::Log;

namespace kxm {
namespace Game {

EventLoopHub::EventLoopHub()
        : shutdownRequested_(false) {
    // Nop.
}

int EventLoopHub::RegisterEventLoop() {
    unique_lock<mutex> critical(lock_);    // Critical section..........................................................
    int id;
    if (unusedLoopSlots_.empty()) {
        id = (int)loops_.size();
        loops_.push_back(LoopInfo());
    }
    else {
        id = unusedLoopSlots_.top();
        unusedLoopSlots_.pop();
    }
    loops_[id].inUse = true;
    Log::Print(Log::Level::Debug, this, [=]{ return "registered event loop, id=" + to_string(id); });
    return id;
}    // ......................................................................................... critical section, end.

void EventLoopHub::UnregisterEventLoop(int clientLoopId) {
    unique_lock<mutex> critical(lock_);    // Critical section..........................................................
    LoopInfo &info = loops_[clientLoopId];
    if (info.inUse) {
        info.inUse = false;
        unusedLoopSlots_.push(clientLoopId);
        Log::Print(Log::Level::Debug, this, [=]{ return "deregistered event loop " + to_string(clientLoopId); });
    }
}    // ......................................................................................... critical section, end.

bool EventLoopHub::RegisterEventIdToSlotMapping(size_t id, int slot) {
    unique_lock<mutex> critical(lock_);    // Critical section..........................................................
    auto iter = eventIdToSlotMap_.find(id);
    if (iter != eventIdToSlotMap_.end()) {
        if (iter->second == slot) {
            return true;
        }
        else {
            return false;
        }
    }

    eventIdToSlotMap_[id] = slot;
    return true;
}    // ......................................................................................... critical section, end.

void EventLoopHub::Post(int clientLoopId, const Core::Buffer &buffer, bool onlyPostToOthers) {
    unique_lock<mutex> critical(lock_);    // Critical section..........................................................
    DoPost(clientLoopId, buffer, onlyPostToOthers);
}    // ......................................................................................... critical section, end.

bool EventLoopHub::GetEvents(int clientLoopId, std::unique_ptr<Core::Buffer> *buffer) {
    unique_lock<mutex> critical(lock_);    // Critical section..........................................................
    while (true) {
        LoopInfo &info = loops_[clientLoopId];
        if (shutdownRequested_) {
            return false;
        }
        else if (!info.buffer->DataSize()) {
            (*buffer)->Clear();
            info.buffer.swap(*buffer);
            return true;
        }
        else {
            info.waiting = true;
            info.stateChanged->wait(critical);
            info.waiting = false;
        }
    }
}    // ......................................................................................... critical section, end.

void EventLoopHub::RequestShutdown() {
    unique_lock<mutex> critical(lock_);    // Critical section..........................................................
    shutdownRequested_ = true;
    for (auto &loopInfo : loops_) {
        if (loopInfo.inUse) {
            loopInfo.stateChanged->notify_all();
        }
    }
}    // ......................................................................................... critical section, end.
 
void EventLoopHub::Post(const Event &event) {
    unique_lock<mutex> critical(lock_);    // Critical section..........................................................
    auto iter = eventIdToSlotMap_.find(event.Type().id);
    assert(iter != eventIdToSlotMap_.end());
    int slot = iter->second;
    eventsToSchedule_.Append(&slot, sizeof(slot));
    event.Serialize(&eventsToSchedule_);
    DoPost(0, eventsToSchedule_, false);
    eventsToSchedule_.Clear();
}    // ......................................................................................... critical section, end.

// Expects lock to be held.
void EventLoopHub::DoPost(int clientLoopId, const Core::Buffer &buffer, bool onlyPostToOthers) {
    int num = static_cast<int>(loops_.size());
    for (int i = 0; i < num; ++i) {
        LoopInfo &loopInfo = loops_[i];
        if (loopInfo.inUse) {
            if (!(onlyPostToOthers && (i == clientLoopId))) {
                loopInfo.buffer->Append(buffer.Data(), buffer.DataSize());    // Ok, if data size is 0.
            }
        }
    }

    // Wake up waiting loop threads for which events are present...
    for (auto &loopInfo : loops_) {
        if (loopInfo.inUse && loopInfo.waiting && loopInfo.buffer->DataSize()) {
            loopInfo.stateChanged->notify_all();
        }
    }
}

}    // Namespace Game.
}    // Namespace kxm.
