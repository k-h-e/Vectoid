#include <Vectoid/SceneGraph/TextConsole.h>

#include <string>
#include <cassert>

using namespace std;

namespace Vectoid {
namespace SceneGraph {

TextConsole::TextConsole(const shared_ptr<Context> &context, int width, int height, float glyphWidth, float glyphHeight,
                         const shared_ptr<Glyphs> &glyphs)
        : Geometry(context),
          glyphWidth_(glyphWidth),
          glyphHeight_(glyphHeight),
          glyphs_(glyphs) {
    Resize(width, height);
}

void TextConsole::WriteLine(const char *line, Color color) {
    int        index             = rowCursor_ * width_;
    uint8_t    *ptr              = &buffer_[index];
    uint8_t    *colorPtr         = &colorBuffer_[index];
    int        num               = 0;
    bool       firstLine         = true;
    const char *currentCharacter = line;
    uint8_t    colorAsUint8      = static_cast<uint8_t>(color);
    while (*currentCharacter) {
        *ptr++      = (uint8_t)*currentCharacter;
        *colorPtr++ = colorAsUint8;
        ++num;
        if (num == width_) {
            num = 0;
            ++rowCursor_;
            if (rowCursor_ == height_) {
                rowCursor_ = 0;
                ptr      = &buffer_[0];
                colorPtr = &colorBuffer_[0];
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

void TextConsole::WriteAt(int column, int row, const char *text, Color color) {
    assert((column >= 0) && (column < width_));
    assert((row    >= 0) && (row    < height_));
    int     index        = row*width_ + column;
    uint8_t *ptr         = &buffer_[index];
    uint8_t *colorPtr    = &colorBuffer_[index];
    uint8_t colorAsUint8 = static_cast<uint8_t>(color);
    while (*text && (column < width_)) {
        *ptr++      = (uint8_t)*text++;
        *colorPtr++ = colorAsUint8;
        ++column;
    }
}

void TextConsole::ClearRow(int row) {
    assert((row >= 0) && (row < height_));
    uint8_t *ptr = &buffer_[row*width_];
    for (int i = 0; i < width_; ++i) {
        *ptr++ = (uint8_t)' ';
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
    colorBuffer_.resize(num);
    for (int i = 0; i < num; ++i) {
        buffer_[i]      = (uint8_t)' ';
        colorBuffer_[i] = static_cast<uint8_t>(Color::White);
    }
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
