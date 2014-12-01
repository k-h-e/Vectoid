//
//  ZarchEvent.cpp
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#include <kxm/Zarch/Events/ZarchEvent.h>

#include <kxm/Core/logging.h>

using namespace std;
using namespace kxm::Core;


namespace kxm {
namespace Zarch {

void ZarchEvent::DispatchToVideo(Video *video) const {
    Log(this).Stream() << "default ZarchEvent::DispatchToVideo() called, event="
                       << Type().name << endl;
}

void ZarchEvent::DispatchToPhysics(Physics *physics) const {
    Log(this).Stream() << "default ZarchEvent::DispatchToPhysics() called, event="
                       << Type().name << endl;
}

void ZarchEvent::DispatchToGameLogic(GameLogic *gameLogic) const {
    Log(this).Stream() << "default ZarchEvent::DispatchToGameLogic() called, event="
                       << Type().name << endl;
}


}    // Namespace Zarch.
}    // Namespace kxm.
