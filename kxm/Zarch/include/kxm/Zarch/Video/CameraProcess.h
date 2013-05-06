//
//  NewCameraProcess.h
//  kxm
//
//  Created by Kai Hergenröther on 4/29/13.
//
//


#ifndef KXM_ZARCH_CAMERAPROCESS_H_
#define KXM_ZARCH_CAMERAPROCESS_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Zarch/Video/Video.h>
#include <kxm/Zarch/processes.h>


namespace kxm {
namespace Zarch {

//! Keeps the camera position in sync with the lander position.
/*!
 *  \ingroup Zarch
 */
class CameraProcess : public ZarchProcess {
  public:
    CameraProcess(const boost::shared_ptr<Video::Data> data);
    
  private:
    CameraProcess(const CameraProcess &other);
    CameraProcess &operator=(const CameraProcess &other);
    //! (Re)implemented.
    bool Execute(const Process::Context &context);
    
    boost::shared_ptr<Video::Data> data_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_CAMERAPROCESS_H_

