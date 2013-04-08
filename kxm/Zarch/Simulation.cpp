//
//  Simulation.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#include <kxm/Zarch/Simulation.h>

using namespace boost;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Simulation::Simulation(shared_ptr<ThreadCouplingBuffer> presentationCouplingBuffer,
                       int sendToPresentationDirection)
        : presentationCouplingBuffer_(presentationCouplingBuffer),
          sendToPresentationDirection_(sendToPresentationDirection) {
}

void Simulation::ExecuteAction() {
}

}
}

