#include <Vectoid/SceneGraph/TextConsole.h>

#include <string>
#include <K/Core/NumberTools.h>
#include <K/Core/StringTools.h>

using std::shared_ptr;
using std::string;
using K::Core::NumberTools;
using K::Core::StringTools;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {

TextConsole::TextConsole(const shared_ptr<Context> &context, int width, int height, float glyphWidth, float glyphHeight,
                         const shared_ptr<Glyphs> &glyphs)
        : Geometry{context},
          glyphWidth_ {glyphWidth },
          glyphHeight_ { glyphHeight },
          frameWidth_ { .25f * glyphWidth_ },
          glyphs_ { glyphs },
          backgroundColor_ { 1.0f, 1.0f, 1.0f },
          backgroundAlpha_ { .125f },
          customColor_ { 1.0f, 1.0f, 1.0f },
          backgroundEnabled_ { true },
          frameColor_ { 1.0f, 1.0f, 1.0f },
          frameEnabled_ { false },
          linesFinished_ { false } {
    Resize(width, height);
}

void TextConsole::WriteLine(const string &line, Color color) {
    uint8_t colorAsUInt8 { static_cast<uint8_t>(color) };
    linesFinished_ = false;
    
    auto words { StringTools::Tokenize(line, " ", true) };
    for (string &word : words) {
        string wordRemainder { word };
        bool   split         { static_cast<int>(word.length()) > width_ };
        while (!wordRemainder.empty()) {
            string partToAdd;
            if (static_cast<int>(wordRemainder.length()) <= numLeftInCurrentRow_) {
                partToAdd     = wordRemainder;
                wordRemainder = "";
            } else {
                if (split) {
                    partToAdd     = wordRemainder.substr(0, numLeftInCurrentRow_);
                    wordRemainder = wordRemainder.substr(numLeftInCurrentRow_);
                } else {
                    FinishLine();
                    partToAdd     = wordRemainder;
                    wordRemainder = "";
                }
            }
            
            for (auto &character : partToAdd) {
                *writePosition_++      = static_cast<uint8_t>(character);
                *colorWritePosition_++ = colorAsUInt8;
                --numLeftInCurrentRow_;
            }
            
            if (numLeftInCurrentRow_) {
                *writePosition_++ = static_cast<uint8_t>(' ');
                ++colorWritePosition_;
                --numLeftInCurrentRow_;
            }
            
            if (!numLeftInCurrentRow_) {
                FinishLine();
            }
        }
    }
    
    if (!linesFinished_ || (numLeftInCurrentRow_ < width_)) {
        FinishLine();
    }
}

void TextConsole::WriteAt(int column, int row, const char *text, Color color) {
    if ((column >= 0) && (column < width_) && (row >= 0) && (row < height_)) {
        int index { row*width_ + column };
        currentRow_          = row;
        numLeftInCurrentRow_ = width_ - column;
        writePosition_       = &buffer_[index];
        colorWritePosition_  = &colorBuffer_[index];
        uint8_t colorAsUint8 { static_cast<uint8_t>(color) };
        while (*text && (column < width_)) {
            *writePosition_++      = (uint8_t)*text++;
            *colorWritePosition_++ = colorAsUint8;
            --numLeftInCurrentRow_;
            ++column;
        }
    }
}

void TextConsole::ClearRow(int row) {
    if ((row >= 0) && (row < height_)) {
        uint8_t *ptr{&buffer_[row*width_]};
        for (int i = 0; i < width_; ++i) {
            *ptr++ = (uint8_t)' ';
        }
    }
}

void TextConsole::Clear() {
    for (int i = 0; i < height_; ++i) {
        ClearRow(i);
    }
    
    currentRow_          = 0;
    numLeftInCurrentRow_ = width_;
    writePosition_       = &buffer_[0];
    colorWritePosition_  = &colorBuffer_[0];
}

void TextConsole::Resize(int width, int height) {
    NumberTools::ClampMin(&width, 1);
    NumberTools::ClampMin(&height, 1);
    width_  = width;
    height_ = height;

    int num { width_ * height_ };
    buffer_.resize(num);
    colorBuffer_.resize(num);
    Clear();
}

Core::BoundingBox<float> TextConsole::BoundingBox() const {
    Core::BoundingBox<float> box;
    box.Grow(Vector<float>(-.5f * static_cast<float>(width_ + 1) * glyphWidth_,
                           -.5f * (static_cast<float>(height_)*glyphHeight_ + glyphWidth_),
                           0.0f));
    box.Grow(Vector<float>(.5f * static_cast<float>(width_ + 1) * glyphWidth_,
                           .5f * (static_cast<float>(height_)*glyphHeight_ + glyphWidth_),
                           0.0f));
    if (frameEnabled_) {
        box.Expand(frameWidth_);
    }
    return box;
}

void TextConsole::EnableBackground(bool enabled) {
    backgroundEnabled_ = enabled;
}

void TextConsole::SetBackgroundColor(const Vector<float> &color, float alpha) {
    backgroundColor_ = color;
    NumberTools::Clamp(&backgroundColor_.x, 0.0f, 1.0f);
    NumberTools::Clamp(&backgroundColor_.y, 0.0f, 1.0f);
    NumberTools::Clamp(&backgroundColor_.z, 0.0f, 1.0f);

    backgroundAlpha_ = alpha;
    NumberTools::Clamp(&backgroundAlpha_, 0.0f, 1.0f);
}

void TextConsole::SetCustomColor(const Vector<float> &color) {
    customColor_ = color;
    NumberTools::Clamp(&customColor_.x, 0.0f, 1.0f);
    NumberTools::Clamp(&customColor_.y, 0.0f, 1.0f);
    NumberTools::Clamp(&customColor_.z, 0.0f, 1.0f);
}

void TextConsole::EnableFrame(bool enabled) {
    frameEnabled_ = enabled;
}

void TextConsole::SetFrameColor(const Vector<float> &color) {
    frameColor_ = color;
    NumberTools::Clamp(&frameColor_.x, 0.0f, 1.0f);
    NumberTools::Clamp(&frameColor_.y, 0.0f, 1.0f);
    NumberTools::Clamp(&frameColor_.z, 0.0f, 1.0f);
}

void TextConsole::SetFrameWidth(float width) {
    if (!(width > 0.0f)) {
        width = .125f * glyphWidth_;
    }
    
    frameWidth_ = width;
}

void TextConsole::FinishLine() {
    while (numLeftInCurrentRow_) {
        *writePosition_++ = static_cast<uint8_t>(' ');
        ++colorWritePosition_;
        --numLeftInCurrentRow_;
    }
    
    ++currentRow_;
    if (currentRow_ >= height_) {
        currentRow_          = 0;
        writePosition_       = &buffer_[0];
        colorWritePosition_  = &colorBuffer_[0];
    }
    
    numLeftInCurrentRow_ = width_;
    
    linesFinished_ = true;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
