//
//  CriticalSection.h
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#ifndef KXM_CORE_CRITICALSECTION_H_
#define KXM_CORE_CRITICALSECTION_H_


namespace kxm {
namespace Core {

//! Critical section (RAII).
/*!
 *  \ingroup Core
 */
class CriticalSection {
  public:
    //! Takes the lock.
    /*!
     *  You can pass <c>0</c> for the lock, in which case the critical section will simply have no
     *  effect.
     *
     *  If given, the lock must outlive the critical section object.
     */
    CriticalSection(LockInterface *lock) : lock_(lock) {
        if (lock_) lock_->Lock();
    };
    //! Releases the lock.
    ~CriticalSection() {
        if (lock_) lock_->Unlock();
    }
    
  private:
    CriticalSection(const CriticalSection &other);
    CriticalSection &operator=(const CriticalSection &other);
    LockInterface *lock_;
};

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_CRITICALSECTION_H_
