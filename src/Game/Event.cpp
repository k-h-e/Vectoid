//
//  Event.cpp
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#include <Game/Event.h>

#include <functional>


namespace kxm {
namespace Game {

Event::EventType::EventType(const char *aName)
        : name(aName),
          id(std::hash<const char *>()(aName)) {
}

}    // Namespace Game.
}    // Namespace kxm.
