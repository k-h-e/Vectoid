#include <kxm/Vectoid/OpenGL/TextConsole.h>

#include <string>
#include <cassert>
#include <kxm/Vectoid/Glyphs.h>
#include <kxm/Vectoid/OpenGL/OpenGL.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace OpenGL {

TextConsole::TextConsole(int width, int height, float glyphWidth, float glyphHeight,
                         shared_ptr<Vectoid::Glyphs> glyphs)
        : Vectoid::TextConsole(width, height, glyphWidth, glyphHeight, glyphs) {
    // Nop.
}

void TextConsole::Render() {
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
        if (rowCursor_ + row == height_) {
            ptr = &buffer_[0];
        }
        float nextY = y - glyphHeight_;
        for (int col = 0; col < width_; ++col) {
            float nextX = x + glyphWidth_;
            if (*ptr != ' ') {
                vertices[ 0] = x;        vertices[ 1] = nextY;
                vertices[ 3] = nextX;    vertices[ 4] = nextY;
                vertices[ 6] = nextX;    vertices[ 7] = y;

                vertices[ 9] = x;        vertices[10] = nextY;
                vertices[12] = nextX;    vertices[13] = y;
                vertices[15] = x;        vertices[16] = y;

                glyphs_->BindGlyphTexture(*ptr);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
            ptr++;
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

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.

