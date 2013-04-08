//
//  ThreadingFactoryInterface.h
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#ifndef KXM_THREADINGFACTORYINTERFACE_H_
#define KXM_THREADINGFACTORYINTERFACE_H_


#include <kxm/Core/Interface.h>


namespace kxm {
namespace Core {

class LockInterface;
class ConditionVariableInterface;
class ThreadControlInterface;

//! Interface to factories creating threading primitives for a given threading mechanism.
/*!
 *  A threading factory instance must be sharable between multiple threads, so its methods are
 *  required to be threadsafe.
 *
 *  \ingroup Core
 */
class ThreadingFactoryInterface : public virtual Interface {
  public:
    //! Creates a lock.
    virtual LockInterface *CreateLock() const = 0;
    //! Creates a condition variable associated with the specified lock.
    /*!
     *  The specified lock must outlive the condition variable.
     */
    virtual ConditionVariableInterface *CreateConditionVariable(LockInterface *associatedLock) const
         = 0;
    //! Creates a thread control object that will allow executing the specified action on an
    //! individual thread.
    virtual ThreadControlInterface *CreateThread() const = 0;
};

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_THREADINGFACTORYINTERFACE_H_
