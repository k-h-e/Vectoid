//
//  NewCameraProcess.h
//  kxm
//
//  Created by Kai Hergenröther on 4/29/13.
//
//


#ifndef KXM_ZARCH_CAMERAPROCESS_H_
#define KXM_ZARCH_CAMERAPROCESS_H_


#include <memory>

#include <Game/ProcessInterface.h>
#include <Zarch/Video/Video.h>


namespace kxm {
namespace Zarch {
namespace Video {

//! Keeps the camera position in sync with the lander position.
/*!
 *  \ingroup ZarchVideo
 */
class CameraProcess : public virtual Game::ProcessInterface {
  public:
    CameraProcess(const std::shared_ptr<Video::Data> data);
    //! (Re)implemented.
    void Execute();
    //! (Re)implemented.
    bool Finished();
    
  private:
    CameraProcess(const CameraProcess &other);
    CameraProcess &operator=(const CameraProcess &other);
    
    std::shared_ptr<Video::Data> data_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_CAMERAPROCESS_H_

