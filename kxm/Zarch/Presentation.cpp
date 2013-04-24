//
//  Presentation.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#include <kxm/Zarch/Presentation.h>

#include <kxm/Game/ThreadCouplingBuffer.h>
#include <kxm/Zarch/Zarch.h>


using namespace boost;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

Presentation::Presentation(shared_ptr<ThreadCouplingBuffer> simulationCouplingBuffer,
                           int sendToSimulationDirection)
        : simulationCouplingBuffer_(simulationCouplingBuffer),
          sendToSimulationDirection_(sendToSimulationDirection) {
    Zarch::RegisterEvents(&eventQueue_);
}

void Presentation::PrepareFrame() {
    ThreadCouplingBuffer::Accessor accessor = simulationCouplingBuffer_->Access(
                                                  sendToSimulationDirection_);
    
    accessor.SignalUpdateForSendDirection();
}

void Presentation::SetViewPort(int width, int height) {
}

void Presentation::RenderFrame() {
}

}
}

