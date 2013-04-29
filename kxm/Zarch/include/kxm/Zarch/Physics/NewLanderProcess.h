//
//  NewLanderProcess.h
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#ifndef KXM_ZARCH_NEWLANDERPROCESS_H_
#define KXM_ZARCH_NEWLANDERPROCESS_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Zarch/Physics/NewPhysics.h>
#include <kxm/Zarch/processes.h>


namespace kxm {
namespace Zarch {

//! Controls the lander (the vehicle controlled by the player).
/*!
 *  \ingroup Zarch
 */
class NewLanderProcess : public ZarchProcess {
  public:
    NewLanderProcess(const boost::shared_ptr<NewPhysics::Data> &data);
    
  private:
    NewLanderProcess(const NewLanderProcess &other);
    NewLanderProcess &operator=(const NewLanderProcess &other);
    //! (Re)implemented.
    bool Execute(const Process::Context &context);
    
    boost::shared_ptr<NewPhysics::Data> data_;
    Vectoid::Vector                     heading_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_NEWLANDERPROCESS_H_
