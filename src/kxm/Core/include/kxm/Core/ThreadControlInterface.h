//
//  ThreadInterface.h
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#ifndef KXM_CORE_THREADCONTROLINTERFACE_H_
#define KXM_CORE_THREADCONTROLINTERFACE_H_


namespace kxm {
namespace Core {

class ActionInterface;

//! Interface to thread control objects.
/*!
 *  \ingroup Core
 *
 *  A thread control object is used to spawn and control a new thread, but it lives in the thread
 *  that instantiated it. It is intended to support \ref Thread, not to be used directly.
 */
class ThreadControlInterface : public virtual Interface {
  public:
    //! Spawns the thread if it has not already been started.
    /*!
     *  \param action
     *  Action to be executed on the spawned thread. The calling context is responsible for
     *  ensuring that the action object lives until the thread terminates.
     */
    virtual void Spawn(ActionInterface *action) = 0;
    //! Waits until the thread has terminated if it has been started, or returns immediately if not.
    virtual void Join() = 0;
};

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_THREADCONTROLINTERFACE_H_
