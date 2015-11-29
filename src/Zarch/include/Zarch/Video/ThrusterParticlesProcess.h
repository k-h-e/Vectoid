//
//  ThrusterParticlesProcess.h
//  kxm
//
//  Created by Kai Hergenroether on 5/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_THRUSTERPARTICLESPROCESS_H_
#define KXM_ZARCH_THRUSTERPARTICLESPROCESS_H_


#include <memory>

#include <Zarch/Video/Video.h>
#include <Zarch/processes.h>


namespace kxm {

namespace Vectoid {
    class Particles;
}

namespace Zarch {

//! Controls the lander's thruster particles.
/*!
 *  \ingroup Zarch
 */
class ThrusterParticlesProcess : public ZarchProcess {
  public:
    ThrusterParticlesProcess(std::shared_ptr<Video::Data> data,
                             std::shared_ptr<Vectoid::Particles> particles);
    bool Execute();
    
  private:
    ThrusterParticlesProcess(const ThrusterParticlesProcess &other);
    ThrusterParticlesProcess &operator=(const ThrusterParticlesProcess &other);
    
    std::shared_ptr<Video::Data>        data_;
    std::shared_ptr<Vectoid::Particles> particles_;
    Vectoid::Vector                     lastLanderPosition_;
    float                               particleTimeCarryOver_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_THRUSTERPARTICLESPROCESS_H_