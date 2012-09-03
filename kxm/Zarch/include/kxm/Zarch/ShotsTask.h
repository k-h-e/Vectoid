//
//  ShotsTask.h
//  kxm
//
//  Created by Kai Hergenroether on 5/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_SHOTSTASK_H_
#define KXM_ZARCH_SHOTSTASK_H_


#include <vector>

#include <boost/shared_ptr.hpp>

#include <kxm/Game/TaskInterface.h>
#include <kxm/Game/FrameTimeTask.h>
#include <kxm/Zarch/LanderTask.h>


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
class ShotsTask : public virtual Game::TaskInterface {
  public:
    ShotsTask(boost::shared_ptr<Vectoid::Particles> particles,
              boost::shared_ptr<const LanderTask::LanderStateInfo> landerState,
              boost::shared_ptr<const Game::FrameTimeTask::FrameTimeInfo> timeInfo,
              boost::shared_ptr<const MapParameters> mapParameters);
    
    void Execute();
    
  private:
    ShotsTask(const ShotsTask &other);
    ShotsTask &operator=(const ShotsTask &other);
    
    boost::shared_ptr<Vectoid::Particles>                       particles_;
    boost::shared_ptr<const LanderTask::LanderStateInfo>        landerState_;
    boost::shared_ptr<const Game::FrameTimeTask::FrameTimeInfo> timeInfo_;
    boost::shared_ptr<const MapParameters>                      mapParameters_;
    float                                                       particleTimeCarryOver_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_SHOTSTASK_H_
