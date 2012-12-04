//
//  StarFieldProcess.h
//  kxm
//
//  Created by Kai Hergenroether on 6/3/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_STARFIELDPROCESS_H_
#define KXM_ZARCH_STARFIELDPROCESS_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Zarch/Video/CameraProcess.h>


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
class StarFieldProcess : public ZarchProcess {
  public:
    StarFieldProcess(boost::shared_ptr<Vectoid::Particles> particles,
                     boost::shared_ptr<const CameraProcess::CameraStateInfo> cameraState,
                     boost::shared_ptr<const MapParameters> mapParameters);
    ~StarFieldProcess() { std::puts("~StarFieldProcess()"); }
    bool Execute(const Process::Context &context);
    
  private:
    StarFieldProcess(const StarFieldProcess &other);
    StarFieldProcess &operator=(const StarFieldProcess &other);
    
    boost::shared_ptr<Vectoid::Particles>                   particles_;
    boost::shared_ptr<const CameraProcess::CameraStateInfo> cameraState_;
    boost::shared_ptr<const MapParameters>                  mapParameters_;
    int                                                     count_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_STARFIELDPROCESS_H_
