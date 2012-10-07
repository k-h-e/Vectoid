//
//  File.cpp
//  kxm
//
//  Created by Kai Hergenröther on 10/7/12.
//
//


#include <kxm/Game/Task.h>


namespace kxm {
namespace Game {

Task::Task()
    : reuseGroup_(NoReuseGroup) {
}

int Task::ReuseGroup() {
    return reuseGroup_;
}

void Task::SetReuseGroup(int reuseGroup) {
    if (reuseGroup >= 0)
        reuseGroup_ = reuseGroup;
    else
        reuseGroup_ = NoReuseGroup;
}

}    // Namespace Game.
}    // Namespace kxm.
