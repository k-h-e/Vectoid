//
//  NewStarFieldProcess.h
//  kxm
//
//  Created by Kai Hergenröther on 4/30/13.
//
//


#ifndef KXM_ZARCH_STARFIELDPROCESS_H_
#define KXM_ZARCH_STARFIELDPROCESS_H_


#include <kxm/Zarch/Video/Video.h>
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
class StarFieldProcess : public ZarchProcess {
  public:
    StarFieldProcess(boost::shared_ptr<Video::Data> data,
                     boost::shared_ptr<Vectoid::Particles> particles);
    bool Execute(const Game::ExecutionContext &context);
    
  private:
    StarFieldProcess(const StarFieldProcess &other);
    StarFieldProcess &operator=(const StarFieldProcess &other);
    
    boost::shared_ptr<Video::Data>        data_;
    boost::shared_ptr<Vectoid::Particles> particles_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_STARFIELDPROCESS_H_
