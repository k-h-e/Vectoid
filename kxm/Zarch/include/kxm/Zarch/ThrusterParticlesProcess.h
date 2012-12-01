//
//  ThrusterParticlesProcess.h
//  kxm
//
//  Created by Kai Hergenroether on 5/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_THRUSTERPARTICLESPROCESS_H_
#define KXM_ZARCH_THRUSTERPARTICLESPROCESS_H_

#include <vector>

#include <boost/shared_ptr.hpp>

#include <kxm/Game/FrameTimeProcess.h>
#include <kxm/Zarch/LanderProcess.h>


namespace kxm {

namespace Vectoid {
    class Particles;
}

namespace Zarch {

class MapParameters;

//! Controls the lander's thruster particles.
/*!
 *  \ingroup Zarch
 */
class ThrusterParticlesProcess : public Game::Process {
  public:
    ThrusterParticlesProcess(
        boost::shared_ptr<Vectoid::Particles> particles,
        boost::shared_ptr<const LanderProcess::LanderStateInfo> landerState,
        boost::shared_ptr<const Game::FrameTimeProcess::FrameTimeInfo> timeInfo,
        boost::shared_ptr<const MapParameters> mapParameters);
    bool Execute();
    
  private:
    ThrusterParticlesProcess(const ThrusterParticlesProcess &other);
    ThrusterParticlesProcess &operator=(const ThrusterParticlesProcess &other);
    
    boost::shared_ptr<Vectoid::Particles>                          particles_;
    boost::shared_ptr<const LanderProcess::LanderStateInfo>        landerState_;
    boost::shared_ptr<const Game::FrameTimeProcess::FrameTimeInfo> timeInfo_;
    boost::shared_ptr<const MapParameters>                         mapParameters_;
    float                                                          particleTimeCarryOver_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_THRUSTERPARTICLESPROCESS_H_
