//
//  ShotsProcess.h
//  kxm
//
//  Created by Kai Hergenroether on 5/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_SHOTSPROCESS_H_
#define KXM_ZARCH_SHOTSPROCESS_H_


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

//! Controls the lander's shots.
/*!
 *  \ingroup Zarch
 */
class ShotsProcess : public Game::Process {
  public:
    ShotsProcess(boost::shared_ptr<Vectoid::Particles> particles,
                 boost::shared_ptr<const LanderProcess::LanderStateInfo> landerState,
                 boost::shared_ptr<const Game::FrameTimeProcess::FrameTimeInfo> timeInfo,
                 boost::shared_ptr<const MapParameters> mapParameters);
    bool Execute();
    
  private:
    ShotsProcess(const ShotsProcess &other);
    ShotsProcess &operator=(const ShotsProcess &other);
    
    boost::shared_ptr<Vectoid::Particles>                          particles_;
    boost::shared_ptr<const LanderProcess::LanderStateInfo>        landerState_;
    boost::shared_ptr<const Game::FrameTimeProcess::FrameTimeInfo> timeInfo_;
    boost::shared_ptr<const MapParameters>                         mapParameters_;
    float                                                          particleTimeCarryOver_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_SHOTSPROCESS_H_
