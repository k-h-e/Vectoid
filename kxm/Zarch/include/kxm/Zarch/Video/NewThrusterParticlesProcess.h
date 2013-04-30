//
//  ThrusterParticlesProcess.h
//  kxm
//
//  Created by Kai Hergenroether on 5/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_NEWTHRUSTERPARTICLESPROCESS_H_
#define KXM_ZARCH_NEWTHRUSTERPARTICLESPROCESS_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Zarch/Video/NewVideo.h>
#include <kxm/Zarch/processes.h>


namespace kxm {

namespace Vectoid {
    class Particles;
}

namespace Zarch {

//! Controls the lander's thruster particles.
/*!
 *  \ingroup Zarch
 */
class NewThrusterParticlesProcess : public ZarchProcess {
  public:
    NewThrusterParticlesProcess(boost::shared_ptr<NewVideo::Data> data,
                                boost::shared_ptr<Vectoid::Particles> particles);
    bool Execute(const Process::Context &context);
    
  private:
    NewThrusterParticlesProcess(const NewThrusterParticlesProcess &other);
    NewThrusterParticlesProcess &operator=(const NewThrusterParticlesProcess &other);
    
    boost::shared_ptr<NewVideo::Data>     data_;
    boost::shared_ptr<Vectoid::Particles> particles_;
    Vectoid::Vector                       lastLanderPosition_;
    float                                 particleTimeCarryOver_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_NEWTHRUSTERPARTICLESPROCESS_H_