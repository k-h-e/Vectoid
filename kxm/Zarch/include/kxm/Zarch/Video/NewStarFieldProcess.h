//
//  NewStarFieldProcess.h
//  kxm
//
//  Created by Kai Hergenröther on 4/30/13.
//
//


#ifndef KXM_ZARCH_NEWSTARFIELDPROCESS_H_
#define KXM_ZARCH_NEWSTARFIELDPROCESS_H_


#include <kxm/Zarch/Video/NewVideo.h>
#include <kxm/Zarch/processes.h>


namespace kxm {

namespace Vectoid {
    class Particles;
}

namespace Zarch {

//! Controls the star field particles.
/*!
 *  \ingroup Zarch
 */
class NewStarFieldProcess : public ZarchProcess {
  public:
    NewStarFieldProcess(boost::shared_ptr<NewVideo::Data> data,
                        boost::shared_ptr<Vectoid::Particles> particles);
    bool Execute(const Process::Context &context);
    
  private:
    NewStarFieldProcess(const NewStarFieldProcess &other);
    NewStarFieldProcess &operator=(const NewStarFieldProcess &other);
    
    boost::shared_ptr<NewVideo::Data>     data_;
    boost::shared_ptr<Vectoid::Particles> particles_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_NEWSTARFIELDPROCESS_H_
