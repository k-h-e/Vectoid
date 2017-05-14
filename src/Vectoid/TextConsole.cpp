#include <kxm/Vectoid/TextConsole.h>

#include <string>
#include <cassert>
#include <kxm/Vectoid/OpenGL.h>
#include <kxm/Vectoid/Glyphs.h>

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

void TextConsole::WriteLine(const string &line) {
    uint8_t *ptr      = &buffer_[rowCursor_ * width_];
    int     num       = 0;
    bool    firstLine = true;
    for (const char &c : line) {
        *ptr++ = (uint8_t)c;
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

void TextConsole::Render(RenderContext *context) {
    GLfloat vertices[]  = { 0.0f, 0.0f, 0.0f,
                            1.0f, 0.0f, 0.0f, 
                            1.0f, 1.0f, 0.0f,
                           
                            0.0f, 0.0f, 0.0f,
                            1.0f, 1.0f, 0.0f,
                            0.0f, 1.0f, 0.0f  };
    
    GLfloat texCoords[] = { 0.0f, 0.0f,
                            1.0f, 0.0f, 
                            1.0f, 1.0f,
                            
                            0.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f  };
    
    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
   	glEnableClientState(GL_VERTEX_ARRAY);
   	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    float left        = -.5f * width_  * glyphWidth_,
          top         =  .5f * height_ * glyphHeight_,
          x           = left,
          y           = top;
    uint8_t *ptr = &buffer_[rowCursor_ * width_];
    for (int row = 0; row < height_; ++row) {
        if (rowCursor_ + row == height_)
            ptr = &buffer_[0];
        float nextY = y - glyphHeight_;
        for (int col = 0; col < width_; ++col) {
            float nextX = x + glyphWidth_;
            vertices[ 0] = x;        vertices[ 1] = nextY;
            vertices[ 3] = nextX;    vertices[ 4] = nextY;
            vertices[ 6] = nextX;    vertices[ 7] = y;

            vertices[ 9] = x;        vertices[10] = nextY;
            vertices[12] = nextX;    vertices[13] = y;
            vertices[15] = x;        vertices[16] = y;

            glyphs_->BindGlyphTexture(*ptr++);
            glDrawArrays(GL_TRIANGLES, 0, 6);
            x = nextX;
        }
        x = left;
        y = nextY;
    }

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

}    // Namespace Vectoid.
}    // Namespace kxm.

