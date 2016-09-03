//
//  NewStarFieldProcess.h
//  kxm
//
//  Created by Kai Hergenröther on 4/30/13.
//
//


#ifndef KXM_ZARCH_STARFIELDPROCESS_H_
#define KXM_ZARCH_STARFIELDPROCESS_H_


#include <memory>

#include <Game/ProcessInterface.h>
#include <Zarch/Video/Video.h>


namespace kxm {

namespace Vectoid {
    class Particles;
}

namespace Zarch {
namespace Video {

//! Controls the star field particles.
/*!
 *  \ingroup ZarchVideo
 */
class StarFieldProcess : public virtual Game::ProcessInterface {
  public:
    StarFieldProcess(std::shared_ptr<Video::Data> data,
                     std::shared_ptr<Vectoid::Particles> particles);
    //! (Re)implemented.
    void Execute();
    //! (Re)implemented.
    bool Finished();
    
  private:
    StarFieldProcess(const StarFieldProcess &other);
    StarFieldProcess &operator=(const StarFieldProcess &other);
    
    std::shared_ptr<Video::Data>        data_;
    std::shared_ptr<Vectoid::Particles> particles_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_STARFIELDPROCESS_H_
