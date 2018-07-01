#include <kxm/Vectoid/TextConsole.h>

#include <string>
#include <cassert>

using namespace std;

namespace kxm {
namespace Vectoid {

TextConsole::TextConsole(int width, int height, float glyphWidth, float glyphHeight,
                         shared_ptr<Glyphs> glyphs)
        : glyphWidth_(glyphWidth),
          glyphHeight_(glyphHeight),
          glyphs_(glyphs) {
    Resize(width, height);
}

void TextConsole::WriteLine(const char *line) {
    uint8_t    *ptr              = &buffer_[rowCursor_ * width_];
    int        num               = 0;
    bool       firstLine         = true;
    const char *currentCharacter = line;
    while (*currentCharacter) {
        *ptr++ = (uint8_t)*currentCharacter;
        ++num;
        if (num == width_) {
            num = 0;
            ++rowCursor_;
            if (rowCursor_ == height_) {
                rowCursor_ = 0;
                ptr = &buffer_[0];
            }
            firstLine = false;
        }
        ++currentCharacter;
    }
    if (firstLine || num) {
        while (num != width_) {
            *ptr++ = (uint8_t)' ';
            ++num;
        }
        ++rowCursor_;
        if (rowCursor_ == height_)
            rowCursor_ = 0;
    }
}

void TextConsole::WriteAt(int column, int row, const char *text) {
    assert((column >= 0) && (column < width_));
    assert((row    >= 0) && (row    < height_));
    uint8_t *ptr = &buffer_[row*width_ + column];
    while (*text && (column < width_)) {
        *ptr++ = (uint8_t)*text++;
        ++column;
    }
}

void TextConsole::Resize(int width, int height) {
    assert(width  > 0);
    assert(height > 0);
    width_     = width;
    height_    = height;
    rowCursor_ = 0;

    int num = width * height;
    buffer_.resize(num);
    for (int i = 0; i < num; ++i) {
        buffer_[i] = 65;
    }
}

}    // Namespace Vectoid.
}    // Namespace kxm.

