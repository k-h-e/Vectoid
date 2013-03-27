//
//  LanderProcess.h
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_LANDERPROCESS_H_
#define KXM_ZARCH_LANDERPROCESS_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Vectoid/Vector.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/FrameTimeProcess.h>
#include <kxm/Zarch/processes.h>


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
class LanderProcess : public ZarchProcess {
  public:
    struct LanderStateInfo {
        Vectoid::Transform transform;
        Vectoid::Vector    velocity;
        bool               thrusterEnabled, firingEnabled;
        
        LanderStateInfo() : thrusterEnabled(false), firingEnabled(false) {}
    };
  
    LanderProcess(boost::shared_ptr<Vectoid::CoordSysInterface> landerCoordSys,
                  boost::shared_ptr<const Game::FrameTimeProcess::FrameTimeInfo> timeInfo,
                  boost::shared_ptr<const Zarch::ControlsState> controlsState,
                  boost::shared_ptr<Terrain> terrain,
                  boost::shared_ptr<const MapParameters> mapParameters);
    
    //! Grants read-only access to the object where the task maintains the lander's state.
    boost::shared_ptr<const LanderStateInfo> LanderState();
    bool Execute(const Process::Context &context);
    
  private:
    LanderProcess(const LanderProcess &other);
    LanderProcess &operator=(const LanderProcess &other);
    
    boost::shared_ptr<Vectoid::CoordSysInterface>                  landerCoordSys_;
    boost::shared_ptr<const Game::FrameTimeProcess::FrameTimeInfo> timeInfo_;
    boost::shared_ptr<const Zarch::ControlsState>                  controlsState_;
    boost::shared_ptr<Terrain>                                     terrain_;
    boost::shared_ptr<const MapParameters>                         mapParameters_;
    boost::shared_ptr<LanderStateInfo>                             landerState_;
    Vectoid::Vector                                                heading_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_LANDERPROCESS_H_
