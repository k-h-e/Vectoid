//
//  NewLanderProcess.h
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#ifndef KXM_ZARCH_LANDERPROCESS_H_
#define KXM_ZARCH_LANDERPROCESS_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Zarch/Physics/Physics.h>
#include <kxm/Zarch/processes.h>


namespace kxm {
namespace Zarch {

//! Controls the lander (the vehicle controlled by the player).
/*!
 *  \ingroup Zarch
 */
class LanderProcess : public ZarchProcess {
  public:
    LanderProcess(const boost::shared_ptr<Physics::Data> &data);
    
  private:
    LanderProcess(const LanderProcess &other);
    LanderProcess &operator=(const LanderProcess &other);
    //! (Re)implemented.
    bool Execute(const Process::Context &context);
    
    boost::shared_ptr<Physics::Data> data_;
    Vectoid::Vector                  heading_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_LANDERPROCESS_H_
