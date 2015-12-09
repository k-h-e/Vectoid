//
//  EventQueueHub.h
//  kxm
//
//  Created by Kai Hergenröther on 11/10/14.
//
//


#ifndef KXM_GAME_EVENTQUEUEHUB_H_
#define KXM_GAME_EVENTQUEUEHUB_H_


#include <memory>
#include <queue>
#include <thread>
#include <condition_variable>


namespace kxm {

namespace Core {
    class Buffer;
}

namespace Game {

//! Hub joining together multiple event queues where each may live in an individual thread.
/*!
 *  \ingroup Game
 */
class EventQueueHub {
  public:
    static const int initialBufferSize = 128;
    
    EventQueueHub();
    EventQueueHub(const EventQueueHub &other)            = delete;
    EventQueueHub &operator=(const EventQueueHub &other) = delete;
    EventQueueHub(EventQueueHub &&other)                 = delete;
    EventQueueHub &operator=(EventQueueHub &&other)      = delete;
    
    //! <b>[Thread-safe]</b> Allocates the resources for another hub client and returns a unique
    //! client id for it.
    int AddClient();
    
    //! <b>[Thread-safe]</b> Allows an \ref EventQueue to sync with the hub.
    /*!
     *  \param buffer
     *  Buffer holding the event data D going into the hub. It will be swapped with another buffer
     *  containing all event data the hub currently has for the calling client, including the event
     *  data D just passed in.
     *
     *  \param inOutWaitSeqNo
     *  If <c>nullptr</c>, the method increments the hub's sequence number and signals a state
     *  change when done. Otherwise it waits until the hub's current sequence number is no longer as
     *  specified by the parameter, and returns the updated sequence number in it.
     *
     *  \return <c>false</c> in case shutdown has been requested.
     */
    bool Sync(int id, std::unique_ptr<Core::Buffer> *buffer, int *inOutWaitSeqNo);
    //! <b>[Thread-safe]</b> Asks all participating threads to shut down (but does not wait for
    //! them to terminate).
    /*!
     *  Participating threads can check for whether shutdown is requested by inspecting the return
     *  value of \ref Sync().
     */
    void RequestShutdown();
    
  private:
    std::mutex                                lock_;
    struct {
        std::vector<std::unique_ptr<Core::Buffer>> buffers;
        int                                        seqNo;
        std::condition_variable                    stateChanged;
        bool                                       shutdownRequested;
    }                                         shared_;    // Protected by lock_.
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_EVENTQUEUEHUB_H_

