//
//  NewCameraProcess.h
//  kxm
//
//  Created by Kai Hergenröther on 4/29/13.
//
//


#ifndef KXM_ZARCH_NEWCAMERAPROCESS_H_
#define KXM_ZARCH_NEWCAMERAPROCESS_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Zarch/Video/NewVideo.h>
#include <kxm/Zarch/processes.h>


namespace kxm {
namespace Zarch {

//! Keeps the camera position in sync with the lander position.
/*!
 *  \ingroup Zarch
 */
class NewCameraProcess : public ZarchProcess {
  public:
    NewCameraProcess(const boost::shared_ptr<NewVideo::Data> data);
    
  private:
    NewCameraProcess(const NewCameraProcess &other);
    NewCameraProcess &operator=(const NewCameraProcess &other);
    //! (Re)implemented.
    bool Execute(const Process::Context &context);
    
    boost::shared_ptr<NewVideo::Data> data_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_NEWCAMERAPROCESS_H_

