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

#include <Game/ProcessInterface.h>
#include <Zarch/Video/Video.h>


namespace kxm {

namespace Vectoid {
    class Particles;
}

namespace Zarch {
namespace Video {

//! Controls the lander's thruster particles.
/*!
 *  \ingroup ZarchVideo
 */
class ThrusterParticlesProcess : public virtual Game::ProcessInterface {
  public:
    ThrusterParticlesProcess(std::shared_ptr<Video::Data> data,
                             std::shared_ptr<Vectoid::Particles> particles);
    //! (Re)implemented.
    void Execute();
    //! (Re)implemented.
    bool Finished();
    
  private:
    ThrusterParticlesProcess(const ThrusterParticlesProcess &other);
    ThrusterParticlesProcess &operator=(const ThrusterParticlesProcess &other);
    
    std::shared_ptr<Video::Data>        data_;
    std::shared_ptr<Vectoid::Particles> particles_;
    Vectoid::Vector                     lastLanderPosition_;
    float                               particleTimeCarryOver_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_THRUSTERPARTICLESPROCESS_H_