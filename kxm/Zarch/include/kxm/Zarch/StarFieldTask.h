//
//  StarFieldTask.h
//  kxm
//
//  Created by Kai Hergenroether on 6/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_STARFIELDTASK_H_
#define KXM_ZARCH_STARFIELDTASK_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Game/TaskInterface.h>
#include <kxm/Zarch/CameraTask.h>


namespace kxm {

namespace Vectoid {
    class Particles;
}

namespace Zarch {

class MapParameters;

//! Controls the star field particles.
/*!
 *  \ingroup Zarch
 */
class StarFieldTask : public virtual Game::Task {
  public:
    StarFieldTask(boost::shared_ptr<Vectoid::Particles> particles,
                  boost::shared_ptr<const CameraTask::CameraStateInfo> cameraState,
                  boost::shared_ptr<const MapParameters> mapParameters);
    bool Execute();
    
  private:
    StarFieldTask(const StarFieldTask &other);
    StarFieldTask &operator=(const StarFieldTask &other);
    
    boost::shared_ptr<Vectoid::Particles>                particles_;
    boost::shared_ptr<const CameraTask::CameraStateInfo> cameraState_;
    boost::shared_ptr<const MapParameters>               mapParameters_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_STARFIELDTASK_H_
