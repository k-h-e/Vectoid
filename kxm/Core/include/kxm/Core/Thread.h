//
//  Thread.h
//  kxm
//
//  Created by Kai Hergenröther on 3/31/13.
//
//


#ifndef KXM_CORE_THREAD_H_
#define KXM_CORE_THREAD_H_


#include <boost/shared_ptr.hpp>


namespace kxm {
namespace Core {

class ActionInterface;
class ThreadingFactoryInterface;
class ThreadControlInterface;

//! Executes an action on an individual thread of execution.
/*!
 *  \ingroup Core
 */
class Thread {
  public:
    //! Spawns a new thread and makes it execute the specified action.
    Thread(const boost::shared_ptr<ActionInterface> &action,
           const ThreadingFactoryInterface &threadingFactory);
    //! Joins the thread (= waits until it has terminated), so be sure to ask the thread to
    //! shut down before letting the receiver go out of scope (if applicable).
    ~Thread();
    
  private:
    Thread(const Thread &other);
    Thread &operator=(const Thread &other);
    
    boost::shared_ptr<ActionInterface>        action_;
    boost::shared_ptr<ThreadControlInterface> threadControl_;
};

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_THREAD_H_

