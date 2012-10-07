//
//  CameraTask.h
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_CAMERATASK_H_
#define KXM_ZARCH_CAMERATASK_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Game/TaskInterface.h>
#include <kxm/Zarch/LanderTask.h>


namespace kxm {

namespace Vectoid {
    class CoordSysInterface;
    class Transform;
}

namespace Zarch {

class MapParameters;

//! Keeps the camera position in sync with the lander position.
/*!
 *  \ingroup Zarch
 */
class CameraTask : public virtual Game::Task {
  public:
    struct CameraStateInfo {
        Vectoid::Vector position;
    };
    
    CameraTask(boost::shared_ptr<Vectoid::CoordSysInterface> cameraCoordSys,
               boost::shared_ptr<const LanderTask::LanderStateInfo> landerState,
               boost::shared_ptr<const MapParameters> mapParameters);
    
    //! Grants read-only access to the object where the task maintains the camera's state.
    boost::shared_ptr<const CameraStateInfo> CameraState();
    bool Execute();
    
  private:
    CameraTask(const CameraTask &other);
    CameraTask &operator=(const CameraTask &other);
    
    boost::shared_ptr<Vectoid::CoordSysInterface>        cameraCoordSys_;
    boost::shared_ptr<const LanderTask::LanderStateInfo> landerState_;
    boost::shared_ptr<const MapParameters>               mapParameters_;
    boost::shared_ptr<CameraStateInfo>                   cameraState_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_CAMERATASK_H_
