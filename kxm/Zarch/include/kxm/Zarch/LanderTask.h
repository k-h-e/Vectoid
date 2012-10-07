//
//  LanderTask.h
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_LANDERTASK_H_
#define KXM_ZARCH_LANDERTASK_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Vectoid/Vector.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/FrameTimeTask.h>

/*!
 *  \defgroup Zarch Game inspired by Zarch
 */


namespace kxm {

namespace Vectoid {
    class CoordSysInterface;
}

namespace Zarch {

class Terrain;
class MapParameters;
class ControlsState;

//! Controls the lander (the vehicle controlled by the player).
/*!
 *  \ingroup Zarch
 */
class LanderTask : public virtual Game::Task {
  public:
    struct LanderStateInfo {
        Vectoid::Transform transform;
        Vectoid::Vector    velocity;
        bool               thrusterEnabled, firingEnabled;
        
        LanderStateInfo() : thrusterEnabled(false), firingEnabled(false) {}
    };
  
    LanderTask(boost::shared_ptr<Vectoid::CoordSysInterface> landerCoordSys,
               boost::shared_ptr<const Game::FrameTimeTask::FrameTimeInfo> timeInfo,
               boost::shared_ptr<const Zarch::ControlsState> controlsState,
               boost::shared_ptr<Terrain> terrain,
               boost::shared_ptr<const MapParameters> mapParameters);
    
    //! Grants read-only access to the object where the task maintains the lander's state.
    boost::shared_ptr<const LanderStateInfo> LanderState();
    bool Execute();
    
  private:
    LanderTask(const LanderTask &other);
    LanderTask &operator=(const LanderTask &other);
    
    boost::shared_ptr<Vectoid::CoordSysInterface>               landerCoordSys_;
    boost::shared_ptr<const Game::FrameTimeTask::FrameTimeInfo> timeInfo_;
    boost::shared_ptr<const Zarch::ControlsState>               controlsState_;
    boost::shared_ptr<Terrain>                                  terrain_;
    boost::shared_ptr<const MapParameters>                      mapParameters_;
    boost::shared_ptr<LanderStateInfo>                          landerState_;
    Vectoid::Vector                                             heading_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_LANDERTASK_H_
