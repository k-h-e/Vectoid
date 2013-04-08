//
//  Presentation.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#include <kxm/Zarch/Presentation.h>

#include <kxm/Game/ThreadCouplingBuffer.h>

using namespace boost;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Presentation::Presentation(shared_ptr<ThreadCouplingBuffer> simulationCouplingBuffer,
                           int sendToSimulationDirection)
        : simulationCouplingBuffer_(simulationCouplingBuffer),
          sendToSimulationDirection_(sendToSimulationDirection) {
}

void Presentation::PrepareFrame() {
    ThreadCouplingBuffer::Accessor simulationCouplingAccess = simulationCouplingBuffer_->Access(
                                                                  sendToSimulationDirection_);
    simulationCouplingAccess.SignalUpdateForSendDirection();
}

void Presentation::SetViewPort(int width, int height) {
}

void Presentation::RenderFrame() {
}

}
}

