//
//  ThreadCouplingBuffer.h
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#ifndef KXM_GAME_THREADCOUPLINGBUFFER_H_
#define KXM_GAME_THREADCOUPLINGBUFFER_H_


#include <kxm/Core/Buffer.h>


namespace kxm {
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
     *  lives (RAII).
     */
    class Accessor {
      public:
        friend class ThreadCouplingBuffer;
        Accessor(const Accessor &other);
        ~Accessor();
        Accessor &operator=(const Accessor &other);
        //! Grants access to the buffer for the specified direction (<c>0</c> or <c>1</c>).
        Core::Buffer &BufferForDirection(int direction);
      private:
        Accessor(ThreadCouplingBuffer *buffer);
        ThreadCouplingBuffer *buffer_;
    };
    
    ThreadCouplingBuffer();
    //! Grants access to the buffer in a threadsafe way, using the RAII scheme.
    Accessor Access();
    
  private:
    ThreadCouplingBuffer(const ThreadCouplingBuffer &other);
    ThreadCouplingBuffer &operator=(const ThreadCouplingBuffer &other);
    void SignOffAccessor();
    
    Core::Buffer buffers_[2];
    int          numAccessors_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_THREADCOUPLINGBUFFER_H_

