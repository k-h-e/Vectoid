#include <K/IO/ListenSocket.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <kxm/Core/logging.h>
#include <K/IO/SocketStream.h>

using std::shared_ptr;
using std::make_shared;
using std::endl;
using kxm::Core::Log;

namespace K {
namespace IO {

ListenSocket::ListenSocket(int port) {
    bool success = false;

    fd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (fd_ != -1) {
        struct sockaddr_in address = {};
        address.sin_family      = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port        = htons(static_cast<uint16_t>(port));
        if (!bind(fd_, (struct sockaddr *)&address, sizeof(address))) {
            if (!listen(fd_, 4)) {
                Log().Stream() << "socket " << fd_ << " listening on port " << port << endl;
                success = true;
            }
        }
        else {
            Log().Stream() << "failed to bind socket " << fd_ << " to port " << port << ", errno=" << errno << endl;
        }
    }

    if (!success) {
        Close();
    }
}

ListenSocket::~ListenSocket() {
    Close();
}

shared_ptr<SocketStream> ListenSocket::Accept() {
    if (fd_ != -1) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressSize = sizeof(clientAddress);
        int connectionFD = accept(fd_, (struct sockaddr *)&clientAddress, &clientAddressSize);
        if (connectionFD != -1) {
            Log().Stream() << "socket " << connectionFD << " accepted connection" << endl;
            return make_shared<SocketStream>(connectionFD);
        }
    }

    return nullptr;
}

void ListenSocket::Close() {
    if (fd_ != -1) {
        Log().Stream() << "closing listen socket " << fd_ << endl;
        close(fd_);
        fd_ = -1;
    }
}

}    // Namesapce IO.
}    // Namespace K.
