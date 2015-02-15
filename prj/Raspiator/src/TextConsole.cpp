#include "TextConsole.h"

#include <cassert>
#include <Vectoid/OpenGL.h>

#include "Glyphs.h"

using namespace std;
using namespace kxm::Vectoid;


namespace Raspiator {

TextConsole::TextConsole(int width, int height, shared_ptr<Glyphs> glyphs)
        : width_(width),
          height_(height),
          glyphs_(glyphs) {
    assert(width  > 0);
    assert(height > 0);

    int num = width * height;
    buffer_.resize(num);
    for (int i = 0; i < num; ++i)
        buffer_[i] = 65;
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

    float glyphWidth  = .15f,
          glyphHeight = .2f,
          left        = -.5f * width_  * glyphWidth,
          top         =  .5f * height_ * glyphHeight,
          x           = left,
          y           = top;
    uint8_t *ptr = &buffer_[0];
    for (int row = 0; row < height_; ++row) {
        float nextY = y - glyphHeight;
        for (int col = 0; col < width_; ++col) {
            float nextX = x + glyphWidth;
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

}    // Namespace Raspiator.

