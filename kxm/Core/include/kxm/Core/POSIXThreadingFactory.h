//
//  POSIXThreadingFactory.h
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#ifndef KXM_POSIXTHREADINGFACTORY_H_
#define KXM_POSIXTHREADINGFACTORY_H_


#include <kxm/Core/ThreadingFactoryInterface.h>


namespace kxm {
namespace Core {

//! Creates <c>POSIX</c> threading primitives.
/*!
 *  \ingroup Core
 */
class POSIXThreadingFactory : public virtual ThreadingFactoryInterface {
  public:
    LockInterface *CreateLock() const;
    ConditionVariableInterface *CreateConditionVariable(LockInterface *associatedLock) const;
    ThreadControlInterface *CreateThread() const;
    
  private:
    class POSIXLock;
    class ConditionVariable;
    class ThreadControl;
};

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_POSIXTHREADINGFACTORY_H_
