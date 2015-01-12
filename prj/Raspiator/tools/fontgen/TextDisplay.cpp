#include "TextDisplay.h"

#include <iostream>
#include <iomanip>
#include <QPainter>

using namespace std;


TextDisplay::TextDisplay()
        : QWidget(nullptr),
          glyphWidth_(0),
          glyphHeight_(0),
          generateCode_(true) {
    font_    = QFont("Monaco", 32);
    metrics_ = unique_ptr<QFontMetrics>(new QFontMetrics(font_));
    glyphs_  = { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P",
                 "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
                 "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p",
                 "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
                 "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
                 ".", ",", "!", "?", "(", ")", "[", "]", "+", "-", "*", "/", "="};

    for (QString &glyph : glyphs_) {
        int width  = metrics_->width(glyph),
            height = metrics_->height();
        if (width  > glyphWidth_)  glyphWidth_  = width;
        if (height > glyphHeight_) glyphHeight_ = height;
    }
}


void TextDisplay::paintEvent(QPaintEvent *event) {
    if (generateCode_)
        cout << hex;

    QPainter painter(this);
    painter.setFont(font_);
    int leftX           = 10,
        rightX          = 500,
        x               = leftX,
        y               = leftX,
        spacing         = 10,
        ascendReduction = 6;
    for (QString &glyph : glyphs_) {
        painter.fillRect(QRect(x, y, glyphWidth_, glyphHeight_ - ascendReduction),
                         QColor(255, 255, 255));
        painter.drawText(QRect(x, y - ascendReduction, glyphWidth_, glyphHeight_), glyph);
        x += glyphWidth_ + spacing;
        if (x + glyphWidth_ >= rightX) {
            y += glyphHeight_ - ascendReduction + spacing;
            x  = leftX;
        }

        if (generateCode_) {
            auto buffer = make_shared<QImage>(glyphWidth_, glyphHeight_, QImage::Format_RGB32);
            QPainter imagePainter(buffer.get());
            imagePainter.setFont(font_);
            imagePainter.fillRect(QRect(0, 0, glyphWidth_, glyphHeight_), QColor(255, 255, 255));
            imagePainter.drawText(QRect(0, 0, glyphWidth_, glyphHeight_), glyph);
            for (int yy = ascendReduction; yy < glyphHeight_; ++yy) {
                cout << "    ";
                for (int xx = 0; xx < glyphWidth_; ++xx) {
                    int grey = qGray(buffer->pixel(xx, yy));
                    cout << "0x" << setfill('0') << setw(2) << grey << ", ";
                }
                cout << endl;
            }
            cout << endl;
        }
    }

    if (generateCode_) {
        for (QString &glyph : glyphs_) {
            char c = (glyph.toStdString())[0];
            cout << "0x" << setfill('0') << setw(2) << (int)c << ", ";
        }
        cout << endl << endl << dec;
        cout << (int)glyphs_.size() << " glyphs of size (" << glyphWidth_ << "x"
             << (glyphHeight_ - ascendReduction) << ")" << endl;
    }

    generateCode_ = false;
}
