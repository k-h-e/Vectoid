//
//  ThreadCouplingBuffer.h
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#ifndef KXM_GAME_THREADCOUPLINGBUFFER_H_
#define KXM_GAME_THREADCOUPLINGBUFFER_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Core/config.h>
#include <kxm/Core/Buffer.h>


namespace kxm {

namespace Core {
    class LockInterface;
    class ConditionVariableInterface;
    class ThreadingFactoryInterface;
}

namespace Game {

//! Buffer for bidirectionally transporting binary data across thread boundaries.
/*!
 *  \ingroup Game
 *
 *  Encapsulates in fact two buffers, one for each transport direction (identified by <c>0</c> and
 *  <c>1</c> respectively).
 */
class ThreadCouplingBuffer {
  public:
    //! Grants access to the buffer in a threadsafe way, using the RAII scheme.
    /*!
     *  \ingroup Game
     *
     *  The accessor must not outlive the buffer. The buffer remains locked as long as the accessor
     *  or any of its copies lives (RAII). All copies of an accessor must live in the same thread.
     */
    class Accessor {
      public:
        friend class ThreadCouplingBuffer;
        Accessor(const Accessor &other);
        ~Accessor();
        Accessor &operator=(const Accessor &other);
        //! Grants access to the buffer for the send direction.
        Core::Buffer &SendBuffer();
        //! Grants access to the buffer for the receive direction.
        Core::Buffer &ReceiveBuffer();
        //! Increments the update sequence number for the send direction and wakes all waiting
        //! threads.
        void SignalUpdateForSendDirection();
        //! Goes to sleep until signalled by another thread via \ref SignalUpdateForSendDirection().
        void Wait();
        //! Gets the current update sequence number for the receive direction.
        uint32_t SeqNoForReceiveDirection();
        //! Raises the shutdown-request flag inside the coupling buffer.
        void RequestShutdown();
        //! Tells whether the shutdown-request flag inside the coupling buffer is set.
        bool ShutdownRequested();
      private:
        Accessor(ThreadCouplingBuffer *buffer, int sendDirection);
        ThreadCouplingBuffer *buffer_;
        int                   sendDirection_;
    };
    
    ThreadCouplingBuffer(const Core::ThreadingFactoryInterface &threadingFactory);
    //! <b>[Threadsafe]</b> Grants access to the buffer in a threadsafe way, using the RAII scheme.
    /*!
     *  The accessor must not outlive the buffer. The buffer remains locked as long as the accessor
     *  or any of its copies lives (RAII). All copies of an accessor must live in the same thread.
     *
     *  \param sendDirection
     *  Specifies which of the two direction buffers is to be used for sending (<c>0</c> or
     *  <c>1</c>).
     */
    Accessor Access(int sendDirection);
    
  private:
    ThreadCouplingBuffer(const ThreadCouplingBuffer &other);
    ThreadCouplingBuffer &operator=(const ThreadCouplingBuffer &other);
    void SignOffAccessor();
    
    boost::shared_ptr<Core::LockInterface>                  lock_;
    Core::spacer_t                                          spacer_;
    struct {
        boost::shared_ptr<Core::ConditionVariableInterface> stateChanged;
        Core::Buffer                                        buffers[2];
        uint32_t                                            seqNos[2];
        int                                                 numAccessors;
        bool                                                shutDownRequested_;
    }                                                       lockProtected_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_THREADCOUPLINGBUFFER_H_

