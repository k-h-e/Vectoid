#include <K/IO/SocketStream.h>

#include <unistd.h>
#include <netdb.h>
#include <vector>
#include <kxm/Core/StringTools.h>
#include <kxm/Core/logging.h>

using std::shared_ptr;
using std::make_shared;
using std::mutex;
using std::unique_lock;
using std::string;
using std::vector;
using std::hex;
using std::dec;
using std::endl;
using kxm::Core::StringTools;
using kxm::Core::Log;

namespace K {
namespace IO {

SocketStream::SocketStream(int fd) {
    if (fd < 0) {
        fd = -1;
    }

    fd_ = fd;
}

SocketStream::~SocketStream() {
    CloseSocket();
}

int SocketStream::Read(void *outBuffer, int bufferSize) {
    int fd;
    {
        unique_lock<mutex> critical(lock_);    // Critical section...
        if (fd_ == -1) {
            return 0;
        }
        fd = fd_;
    }    // ... critical section, end.

    int num = read(fd_, outBuffer, bufferSize);
    if (num == -1) {
        CloseSocket();
        num = 0;
    }
    return num;
}

int SocketStream::Write(const void *data, int dataSize) {
    int fd;
    {
        unique_lock<mutex> critical(lock_);    // Critical section...
        if (fd_ == -1) {
            return 0;
        }
        fd = fd_;
    }    // ... critical section, end.

    int num = write(fd_, data, dataSize);
    if (num == -1) {
        CloseSocket();
        num = 0;
    }
    return num;
}

bool SocketStream::EndOfStream() {
    return false;
}

bool SocketStream::Error() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    return (fd_ == -1);
}    // ... critical section, end.

void SocketStream::CloseSocket() {
    unique_lock<mutex> critical(lock_);    // Critical section...
    if (fd_ != -1) {
        close(fd_);
        Log().Stream() << "socket " << fd_ << " closed" << endl;
        fd_ = -1;
    }
}    // ... critical section, end.

shared_ptr<SocketStream> SocketStream::ConnectToHost(const string &host) {
    vector<string> tokens;
    StringTools::Tokenize(host, ':', &tokens);
    if (tokens.size() == 2) {
        int port;
        if (StringTools::Parse(tokens[1], &port)) {
            Log().Stream() << "port is " << port << endl;
            uint32_t ip4Address;
            if (ResolveHostName(tokens[0], &ip4Address)) {
                return ConnectToHost(ip4Address, port);
            }
        }
    }

    return nullptr;
}

shared_ptr<SocketStream> SocketStream::ConnectToHost(uint32_t ip4Address, int port) {
    int fd = socket(PF_INET, SOCK_STREAM, 0);
    if (fd != -1) {
        struct sockaddr_in address = {};
        address.sin_family      = AF_INET;
        address.sin_addr.s_addr = htonl(ip4Address);
        address.sin_port        = htons(static_cast<uint16_t>(port));
        if (!connect(fd, (struct sockaddr *)&address, sizeof(address))) {
            Log().Stream() << "socket " << fd << " connected to ip4=0x" << hex << (unsigned int)ip4Address << ", port="
                           << dec << port << endl;
            return make_shared<SocketStream>(fd);
        }

        close (fd);
    }

    return nullptr;
}

bool SocketStream::ResolveHostName(const string &hostName, uint32_t *outIp4Address) {
    Log().Stream() << "resolving host name \"" << hostName << "\"..." << endl;

    struct addrinfo *result = nullptr;
    struct addrinfo hints   = { };
    hints.ai_family = PF_INET;
    if (!getaddrinfo(hostName.c_str(), nullptr, &hints, &result)) {
        uint32_t ip;
        struct addrinfo *current = result;
        while(current) {
            if(current->ai_family == PF_INET) {
              ip = ntohl(((struct sockaddr_in *)(current->ai_addr))->sin_addr.s_addr);
              break;
           }
           current = current->ai_next;
        }
        freeaddrinfo(result);

        if (current) {
            *outIp4Address = ip;
            return true;
        }
    }

    return false;
}

}    // Namesapce IO.
}    // Namespace K.
