#include <K/IO/ListenSocket.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

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
                success = true;
            }
        }
    }

    if (!success) {
        Close();
    }
}

ListenSocket::~ListenSocket() {
    Close();
}

int ListenSocket::Accept() {
    if (fd_ != -1) {
        struct sockaddr_in clientAddress;
        socklen_t clientAddressSize = sizeof(clientAddress);
        int connectionFD = accept(fd_, (struct sockaddr *)&clientAddress, &clientAddressSize);
        if (connectionFD != -1) {
            return connectionFD;
        }
    }

    return -1;
}

void ListenSocket::Close() {
    if (fd_ != -1) {
        close(fd_);
        fd_ = -1;
    }
}

}    // Namesapce IO.
}    // Namespace K.
