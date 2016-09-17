//
//  Event.cpp
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#include <kxm/Game/Event.h>

#include <functional>


namespace kxm {
namespace Game {

Event::EventType::EventType(const char *aName)
        : name(aName),
          id(std::hash<const char *>()(aName)) {
}

void Event::Serialize(Core::Buffer *targetBuffer) const {
}

void Event::Deserialize(Core::Buffer::Reader *bufferReader) {
}

}    // Namespace Game.
}    // Namespace kxm.
