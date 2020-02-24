#ifndef K_IO_STREAMINTERFACE_H_
#define K_IO_STREAMINTERFACE_H_

#include <kxm/Core/Interface.h>

namespace K {
namespace IO {

//! Base interface to streams.
/*!
 *  \ingroup IO
 */
class StreamInterface : public virtual kxm::Core::Interface {
  public:
    //! Tells whether or not the stream has entered error state.
    /*!
     *  When in error state, all I/O operations on the stream have no effect and indicate failure.
     *
     *  Once the stream has entered error state, it does not automatically leave it again.
     */
    virtual bool IOError() = 0;
};

}    // Namespace IO.
}    // Namespace K.

#endif    // K_IO_STREAMINTERFACE_H_
