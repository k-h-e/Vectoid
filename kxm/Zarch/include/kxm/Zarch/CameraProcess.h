//
//  CameraProcess.h
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_CAMERAPROCESS_H_
#define KXM_ZARCH_CAMERAPROCESS_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Zarch/LanderProcess.h>


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
class CameraProcess : public Game::Process {
  public:
    struct CameraStateInfo {
        Vectoid::Vector position;
    };
    
    CameraProcess(boost::shared_ptr<Vectoid::CoordSysInterface> cameraCoordSys,
                  boost::shared_ptr<const LanderProcess::LanderStateInfo> landerState,
                  boost::shared_ptr<const MapParameters> mapParameters);
    
    //! Grants read-only access to the object where the task maintains the camera's state.
    boost::shared_ptr<const CameraStateInfo> CameraState();
    bool Execute();
    
  private:
    CameraProcess(const CameraProcess &other);
    CameraProcess &operator=(const CameraProcess &other);
    
    boost::shared_ptr<Vectoid::CoordSysInterface>           cameraCoordSys_;
    boost::shared_ptr<const LanderProcess::LanderStateInfo> landerState_;
    boost::shared_ptr<const MapParameters>                  mapParameters_;
    boost::shared_ptr<CameraStateInfo>                      cameraState_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_CAMERAPROCESS_H_
