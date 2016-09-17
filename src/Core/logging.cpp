#include <kxm/Core/logging.h>

#include <iostream>

using namespace std;

namespace kxm {
namespace Core {

LoggerHandle Log(const void *origin) {
    return LoggerHandle(&cout);
}

LoggerHandle Log() {
    return Log(0);
}

LoggerHandle::LoggerHandle(ostream *outStream)
    : stream_(outStream),
      haveToUnlock_(true) {
    // TODO : lock stream!
}

LoggerHandle::LoggerHandle(const LoggerHandle &other) {
    *this = other;
}

LoggerHandle::LoggerHandle() {
    stream_       = &cout;
    haveToUnlock_ = false;
}

LoggerHandle::~LoggerHandle() {
    if (haveToUnlock_)
        ;    // TODO : unlock stream!
}

LoggerHandle &LoggerHandle::operator=(const LoggerHandle &other) {
    stream_ = other.stream_;
    if (other.haveToUnlock_) {
        haveToUnlock_                                   = true;
        const_cast<LoggerHandle &>(other).haveToUnlock_ = false;
    }
    else {
        haveToUnlock_ = false;
    }
    return *this;
}    

std::ostream &LoggerHandle::Stream() {
    return *stream_;
}

}    // Namespace Core.
}    // Namespace kxm.
