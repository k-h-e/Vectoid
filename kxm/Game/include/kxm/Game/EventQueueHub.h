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
    
    EventQueueHub();
    EventQueueHub(const EventQueueHub &other)            = delete;
    EventQueueHub &operator=(const EventQueueHub &other) = delete;
    EventQueueHub(EventQueueHub &&other)                 = delete;
    EventQueueHub &operator=(EventQueueHub &&other)      = delete;
    
    //! Get a unique client id to be used with a specific event queue.
    ClientId GetUniqueClientId();
    
    //! <b>[Thread-safe]</b>Allows an \ref EventQueue to sync with the hub.
    /*!
     *  \param toHubBuffer
     *  Buffer holding the event data going into the hub. The client's buffer will be swapped with
     *  another, empty one from a pool managed by the hub. Can be <c>nullptr</c>, in which case
     *  no data is sent to the hub, but an empty buffer is provided to the client nonetheless.
     *
     *  \param toQueueBuffer
     *  This buffer will accept the event data going from the hub into the queue. It will get
     *  cleared by the hub before new data is written.
     */
    void Sync(ClientId id, std::unique_ptr<Core::Buffer> *toHubBuffer, Core::Buffer *toQueueBuffer,
              bool wait);
    
  private:
    struct BufferInfo {
        std::unique_ptr<Core::Buffer> buffer;
        unsigned int                  unreadBits;
        BufferInfo(std::unique_ptr<Core::Buffer> &&aBuffer, unsigned int someUnreadBits);
    };
    
    std::mutex                                    lock_;
    struct {
        std::deque<BufferInfo>                        activeBuffers;
        std::queue<std::unique_ptr<Core::Buffer>>     bufferPool;
        unsigned int                                  nextId,
                                                      toReadMask;
    }                                             shared_;    // Protected by lock_.
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_EVENTQUEUEHUB_H_

