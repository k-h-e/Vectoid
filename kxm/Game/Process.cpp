//
//  Process.cpp
//  kxm
//
//  Created by Kai Hergenröther on 12/1/12.
//
//


#include <kxm/Game/Process.h>


namespace kxm {
namespace Game {

Process::Process()
        : type_(-1),
          next_(0),
          prev_(0) {
}

bool Process::Execute() {
    return true;
}

}    // Namespace Game.
}    // Namespace kxm.
