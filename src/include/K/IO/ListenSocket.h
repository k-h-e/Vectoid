/*!
 *  \defgroup IO IO
 *  \brief I/O.
 */

#ifndef K_IO_LISTENSOCKET_H_
#define K_IO_LISTENSOCKET_H_

#include <memory>

namespace K {
namespace IO {

class SocketStream;

//! Listen socket.
/*!
 *  \ingroup IO
 */
class ListenSocket {
  public:
    ListenSocket(int port);
    ListenSocket(const ListenSocket &other) = delete;
    ListenSocket &operator=(const ListenSocket &other) = delete;
    ~ListenSocket();

    //! Accepts a new connection from the listen socket.
    /*!
     *  \return
     *  <c>null</c> handle in case of failure.
     */
    std::shared_ptr<SocketStream> Accept();

  private:
    void Close();

    int fd_;
};

}    // Namespace IO.
}    // Namespace K.

#endif    // K_IO_LISTENSOCKET_H_
