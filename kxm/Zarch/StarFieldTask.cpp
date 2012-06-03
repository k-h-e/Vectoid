//
//  StarFieldTask.cpp
//  kxm
//
//  Created by Kai Hergenroether on 6/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/StarFieldTask.h>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <kxm/Vectoid/Particles.h>
#include <kxm/Zarch/MapParameters.h>

using boost::shared_ptr;
using namespace boost::random;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

StarFieldTask::StarFieldTask(shared_ptr<Particles> particles,
                             shared_ptr<const LanderTask::LanderStateInfo> landerState,
                             shared_ptr<const MapParameters> mapParameters)
        : particles_(particles),
          landerState_(landerState),
          mapParameters_(mapParameters) {
    const int                  randomMax = 10000;
    mt19937                    randomGenerator;
    uniform_int_distribution<> randomDistribution(0, randomMax);
    for (int i = 0; i < mapParameters_->numStars; i++) {
    }
}

void StarFieldTask::Execute() {
}


}    // Namespace Zarch.
}    // Namespace kxm.
