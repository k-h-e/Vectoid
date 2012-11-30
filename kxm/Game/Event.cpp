//
//  Event.cpp
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//


#include <kxm/Game/Event.h>


namespace kxm {
namespace Game {

Event::Event() {
    type_ = -1;
}

Event::~Event() {
}

int Event::Type() {
    return type_;
}

void Event::SetType(int type) {
    type_ = type;
}

}    // Namespace Game.
}    // Namespace kxm.
