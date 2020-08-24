#include <Vectoid/SceneGraph/OpenGL/TextConsole.h>

#include <string>
#include <cassert>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/Glyphs.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using namespace std;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

TextConsole::TextConsole(int width, int height, float glyphWidth, float glyphHeight,
                         const shared_ptr<SceneGraph::Glyphs> &glyphs)
        : SceneGraph::TextConsole(width, height, glyphWidth, glyphHeight, glyphs),
          currentColorIndex_(0u) {
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

    currentColorIndex_ = 1u;
    SetColor(0u);

    float left        = -.5f * width_  * glyphWidth_,
          top         =  .5f * height_ * glyphHeight_,
          x           = left,
          y           = top;
    uint8_t *ptr      = &buffer_[0];
    uint8_t *colorPtr = &colorBuffer_[0];
    for (int row = 0; row < height_; ++row) {
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

                SetColor(*colorPtr);
                glyphs_->BindGlyphTexture(*ptr);
                glDrawArrays(GL_TRIANGLES, 0, 6);
            }
            ptr++;
            colorPtr++;
            x = nextX;
        }
        x = left;
        y = nextY;
    }

    glColor3f(1.0f, 1.0f, 1.0f);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void TextConsole::SetColor(uint8_t colorIndex) {
    if (colorIndex != currentColorIndex_) {
        Vector<float> color;
        switch (colorIndex) {
            case 0u:
                color = Vector<float>(1.0f, 1.0f, 1.0f);
                break;
            case 1u:
                color = Vector<float>(0.5f, 0.5f, 0.5f);
                break;
            case 2u:
                color = Vector<float>(0.0f, 1.0f, 0.0f);
                break;
            case 3u:
                color = Vector<float>(1.0f, 1.0f, 0.0f);
                break;
            case 4u:
                color = Vector<float>(1.0f, 0.0f, 0.0f);
                break;
            default:
                break;
        }
        glColor3f(color.x, color.y, color.z);

        currentColorIndex_ = colorIndex;
    }
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

