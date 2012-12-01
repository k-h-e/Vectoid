//
//  ProcessPool.h
//  kxm
//
//  Created by Kai Hergenröther on 11/29/12.
//
//


#ifndef KXM_GAME_PROCESSPOOL_H_
#define KXM_GAME_PROCESSPOOL_H_


#include <kxm/Core/Pool.h>
#include <kxm/Game/ProcessPoolInterface.h>


namespace kxm {
namespace Game {

//! Adapter for \ref Pool<T>, so pool instances for different process types can be used with the
//! \ref Processes mechanism.
/*!
 *  \ingroup Game
 */
template<class T>
class ProcessPool : public virtual ProcessPoolInterface {
  public:
    ProcessPool() {}
    Process *Get() { return pool_.Get(); }
    void Put(Process *process) { pool_.Put(static_cast<T *>(process)); }
    
  private:
    ProcessPool(const ProcessPool &other);
    ProcessPool &operator=(const ProcessPool &other);
  
    Core::Pool<T> pool_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_PROCESSPOOL_H_
