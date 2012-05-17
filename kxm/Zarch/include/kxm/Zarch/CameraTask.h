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

//! Keeps the camera position in sync with the lander position.
/*!
 *  \ingroup Zarch
 */
class CameraTask : public virtual Game::TaskInterface {
  public:
    CameraTask(boost::shared_ptr<Vectoid::CoordSysInterface> cameraCoordSys,
               boost::shared_ptr<const LanderTask::LanderStateInfo> landerState);
    
    void Execute();
    
  private:
    CameraTask(const CameraTask &other);
    CameraTask &operator=(const CameraTask &other);
    
    boost::shared_ptr<Vectoid::CoordSysInterface>        cameraCoordSys_;
    boost::shared_ptr<const LanderTask::LanderStateInfo> landerState_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_CAMERATASK_H_
