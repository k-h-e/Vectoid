//
//  ConditionVariableInterface.h
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#ifndef KXM_CORE_CONDITIONVARIABLEINTERFACE_H_
#define KXM_CORE_CONDITIONVARIABLEINTERFACE_H_


namespace kxm {
namespace Core {

//! Interface to condition variables.
/*!
 *  \ingroup Core
 *
 *  A condition variable is always associated with a lock (as implemented by \ref LockInterface),
 *  and the lock is required to outlive the condition variable.
 */
class ConditionVariableInterface : public virtual Interface {
  public:
    //! Goes to sleep on the condition variable until signalled by another thread.
    virtual void Wait() = 0;
    //! Signals (wakes) all threads waiting on the condition variable.
    virtual void SignalAll() = 0;
};

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_CONDITIONVARIABLEINTERFACE_H_
