//
//  EventLoopHub.h
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//

#ifndef KXM_GAME_EVENTLOOPHUB_H_
#define KXM_GAME_EVENTLOOPHUB_H_

#include <memory>
#include <queue>
#include <thread>
#include <condition_variable>
#include <kxm/Core/Buffer.h>

namespace kxm {
namespace Game {

//! Hub joining together multiple \ref EventLoop s where each lives in an individual thread.
/*!
 *  \ingroup Game
 */
class EventLoopHub {
  public:
    EventLoopHub();
    EventLoopHub(const EventLoopHub &other)            = delete;
    EventLoopHub &operator=(const EventLoopHub &other) = delete;
    EventLoopHub(EventLoopHub &&other)                 = delete;
    EventLoopHub &operator=(EventLoopHub &&other)      = delete;
    
    //! <b>[Thread-safe]</b> Allocates the resources for another client \ref EventLoop and returns a unique client id
    //! for it.
    int AddEventLoop();
    
    //! <b>[Thread-safe]</b> Schedules the events represented by the serialized event data in the specified buffer.
    void ScheduleEvents(const std::unique_ptr<Core::Buffer> &buffer);
    
    //! <b>[Thread-safe]</b> Allows a client \ref EventLoop (thread) to retrieve all events currently scheduled for it.
    /*!
     *  If currently there are no more events schedlued for the calling client \ref EventLoop, the method blocks the
     *  client loop's thread until new events arrive for it (or shutdown is requested).
     *
     *  \param buffer
     *  Some buffer no longer needed by the client \ref EventLoop. It will be swapped with another buffer containing all
     *  event data the hub currently has for the calling client \ref EventLoop.
     *
     *  \return <c>false</c> in case shutdown has been requested.
     */
    bool GetEvents(int clientLoopId, std::unique_ptr<Core::Buffer> *buffer);
    
    //! <b>[Thread-safe]</b> Asks all participating client \ref EventLoop s to finish running (but does not wait until
    //! that has happened).
    /*!
     *  Participating client \ref EventLoop s can check for whether shutdown is requested by inspecting the return
     *  value of \ref GetEvents().
     */
    void RequestShutdown();
    
  private:
    struct LoopInfo {
        std::unique_ptr<Core::Buffer>            buffer;
        std::unique_ptr<std::condition_variable> stateChanged;
        bool                                     waiting;
        LoopInfo()
            : buffer(new Core::Buffer()),
              stateChanged(new std::condition_variable()),
              waiting(false) {}
    };
    
    std::mutex                lock_;
    struct {
        std::vector<LoopInfo> loops;
        bool                  shutdownRequested;
    }                         shared_;    // Protected by lock_.
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_EVENTLOOPHUB_H_

