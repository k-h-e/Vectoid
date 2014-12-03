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
    typedef unsigned int ClientId;
    static const int initialBufferSize = 128;
    
    EventQueueHub();
    EventQueueHub(const EventQueueHub &other)            = delete;
    EventQueueHub &operator=(const EventQueueHub &other) = delete;
    EventQueueHub(EventQueueHub &&other)                 = delete;
    EventQueueHub &operator=(EventQueueHub &&other)      = delete;
    
    //! <b>[Thread-safe]</b> Allocates a unique client id to be used with a specific event queue.
    ClientId AllocUniqueClientId();
    
    //! <b>[Thread-safe]</b> Allows an \ref EventQueue to sync with the hub.
    /*!
     *  \param toHubBuffer
     *  Buffer holding the event data going into the hub. The client's buffer will be swapped with
     *  another, empty one from a pool managed by the hub. Can be <c>nullptr</c>, in which case
     *  no data is sent to the hub, but an empty buffer is provided to the client nonetheless.
     *
     *  \param toQueueBuffer
     *  This buffer will accept the event data going from the hub into the queue. It will get
     *  cleared by the hub before new data is written.
     *
     *  \return <c>false</c> in case shutdown has been requested.
     */
    bool Sync(ClientId id, std::unique_ptr<Core::Buffer> *toHubBuffer, Core::Buffer *toQueueBuffer,
              bool wait);
    //! <b>[Thread-safe]</b> Asks all participating threads to shut down (but does not wait for
    //! them to terminate).
    /*!
     *  Participating threads can check for whether shutdown is requested by inspecting the return
     *  value of \ref Sync().
     */
    void RequestShutdown();
    
  private:
    struct BufferInfo {
        std::unique_ptr<Core::Buffer> buffer;
        unsigned int                  unreadBits;
        BufferInfo(std::unique_ptr<Core::Buffer> &&aBuffer, unsigned int someUnreadBits);
    };
    
    std::mutex                                    lock_;
    struct {
        std::condition_variable                       stateChanged;
        std::deque<BufferInfo>                        activeBuffers;
        std::queue<std::unique_ptr<Core::Buffer>>     bufferPool;
        unsigned int                                  nextId,
                                                      toReadMask;
        bool                                          shutdownRequested;
    }                                             shared_;    // Protected by lock_.
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_EVENTQUEUEHUB_H_

