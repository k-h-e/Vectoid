#include <K/IO/IOTools.h>

#include <stdint.h>
#include <K/IO/StreamInputInterface.h>
#include <K/IO/StreamOutputInterface.h>

namespace K {
namespace IO {

bool ReadItem(StreamInputInterface *stream, void *outItem, int itemSize) {
    uint8_t *target      = static_cast<uint8_t *>(outItem);
    int     numRemaining = itemSize;
    while (numRemaining > 0) {
        int num = stream->Read(target, numRemaining);
        if (num > 0) {
            target       += num;
            numRemaining -= num;
        }
        else {
            if (stream->Error() || stream->EndOfStream()) {
                return false;
            }
        }
    }
    return true;
}

bool WriteItem(StreamOutputInterface *stream, const void *item, int itemSize) {
    const uint8_t *source      = static_cast<const uint8_t *>(item);
    int           numRemaining = itemSize;
    while (numRemaining > 0) {
        int num = stream->Write(source, numRemaining);
        if (num > 0) {
            source       += num;
            numRemaining -= num;
        }
        else {
            if (stream->Error()) {
                return false;
            }
        }
    }
    return true;
}

}    // Namespace IO.
}    // Namespace K.
