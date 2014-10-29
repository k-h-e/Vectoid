//
//  EventQueue.cpp
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#include <kxm/Game/EventQueue.h>

#include <cassert>
#include <kxm/Core/logging.h>
#include <kxm/Game/Event.h>

using namespace kxm::Core;

namespace kxm {
namespace Game {

EventQueue::EventQueue() {
    // Nop.
}

void EventQueue::RegisterEvent(std::unique_ptr<Event> protoType) {
    assert(protoType.get() != nullptr);
    size_t id             = protoType->Type().id;
    bool   alreadyPresent = (idToSlotMap_.find(id) != idToSlotMap_.end());
    if (alreadyPresent)
        Log().Stream() << "hash collision while registering event \"" << protoType->Type().name
                       << "\"" << std::endl;
    assert(!alreadyPresent);
    int slot = (int)events_.size();
    events_.push_back(EventInfo(std::move(protoType)));
    idToSlotMap_[id] = slot;
}

}    // Namespace Game.
}    // Namespace kxm.