//
//  NewLanderProcess.h
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#ifndef KXM_ZARCH_LANDERPROCESS_H_
#define KXM_ZARCH_LANDERPROCESS_H_


#include <memory>

#include <Game/ProcessInterface.h>
#include <Zarch/Physics/Physics.h>


namespace kxm {
namespace Zarch {

//! Controls the lander (the vehicle controlled by the player).
/*!
 *  \ingroup Zarch
 */
class LanderProcess : public virtual Game::ProcessInterface {
  public:
    LanderProcess(const std::shared_ptr<Physics::Data> &data);
    //! (Re)implemented.
    void Execute();
    //! (Re)implemented.
    bool Finished();
    
  private:
    LanderProcess(const LanderProcess &other);
    LanderProcess &operator=(const LanderProcess &other);
    
    std::shared_ptr<Physics::Data> data_;
    Vectoid::Vector                heading_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_LANDERPROCESS_H_
