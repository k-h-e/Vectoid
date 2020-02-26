#ifndef K_IO_SOCKETSTREAM_H_
#define K_IO_SOCKETSTREAM_H_

#include <memory>
#include <mutex>
#include <K/IO/StreamIOInterface.h>

namespace K {
namespace IO {

//! Socket stream.
/*!
 *  \ingroup IO
 *
 *  The class is thread-safe (i.e. all public methods).
 */
class SocketStream : public virtual StreamIOInterface {
  public:
    SocketStream(int fd);
    SocketStream(const SocketStream &other)            = delete;
    SocketStream &operator=(const SocketStream &other) = delete;
    ~SocketStream();

    //! Closes the stream if it is still open.
    void Close();

    virtual int Read(void *outBuffer, int bufferSize);
    virtual int Write(const void *data, int dataSize);
    virtual bool EndOfStream();
    virtual bool IOError();

    //! Establishes a network stream connection to a host given by name and port, separated by a <c>':'</c>.
    /*!
     *  \return
     *  <c>null</c> handle in case of failure.
     */
    static std::shared_ptr<SocketStream> ConnectToHost(const std::string &host);
    //! Establishes a network stream connection to the specified host.
    /*!
     *  \return
     *  <c>null</c> handle in case of failure.
     */
    static std::shared_ptr<SocketStream> ConnectToHost(uint32_t ip4Address, int port);
    //! Resolves the specified host name.
    /*!
     *  \return
     *  <c>false</c> in case of failure. The output parameter will then be undefined.
     */
    static bool ResolveHostName(const std::string &hostName, uint32_t *outIp4Address);

  private:
    // Expects the lock to be held.
    void CloseSocket();

    std::mutex lock_;
    int        fd_;
    bool       eof_;
    bool       error_;
};

}    // Namespace IO.
}    // Namespace K.

#endif    // K_IO_SOCKETSTREAM_H_
