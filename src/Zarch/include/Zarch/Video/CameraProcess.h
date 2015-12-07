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

//! Keeps the camera position in sync with the lander position.
/*!
 *  \ingroup Zarch
 */
class CameraProcess : public virtual Game::ProcessInterface {
  public:
    CameraProcess(const std::shared_ptr<Video::Data> data);
    
  private:
    CameraProcess(const CameraProcess &other);
    CameraProcess &operator=(const CameraProcess &other);
    //! (Re)implemented.
    void Execute();
    //! (Re)implemented.
    bool Finished();
    
    std::shared_ptr<Video::Data> data_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_CAMERAPROCESS_H_

