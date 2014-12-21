//
//  LockInterface.h
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#ifndef KXM_CORE_LOCKINTERFACE_H_
#define KXM_CORE_LOCKINTERFACE_H_


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Core {

//! Interface to locks.
/*!
 *  \ingroup Core
 */
class LockInterface : public virtual Interface {
  public:
    //! Locks the lock.
    virtual void Lock() = 0;
    //! Unlocks the lock.
    virtual void Unlock() = 0;
};

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_LOCKINTERFACE_H_
