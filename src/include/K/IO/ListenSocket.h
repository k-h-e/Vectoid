/*!
 *  \defgroup IO IO
 *  \brief I/O.
 */

#ifndef K_IO_LISTENSOCKET_H_
#define K_IO_LISTENSOCKET_H_

namespace K {
namespace IO {

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

    int Accept();

  private:
    void Close();

    int fd_;
};

}    // Namespace IO.
}    // Namespace K.

#endif    // K_IO_LISTENSOCKET_H_
