#include <Vectoid/SceneGraph/OpenGL/TextConsole.h>

#include <string>
#include <cassert>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/Glyphs.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::shared_ptr;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

TextConsole::TextConsole(const shared_ptr<Context> &context, int width, int height, float glyphWidth, float glyphHeight,
                         const shared_ptr<SceneGraph::Glyphs> &glyphs)
        : SceneGraph::TextConsole(context, width, height, glyphWidth, glyphHeight, glyphs),
          currentColorIndex_(0u) {
    // Nop.
}

void TextConsole::Render() {
    float left             = -.5f * width_  * glyphWidth_;
    float top              =  .5f * height_ * glyphHeight_;
    float margin           = .5f * glyphWidth_;
    float backgroundLeft   = left - margin;
    float backgroundRight  = -backgroundLeft;
    float backgroundTop    = top + margin;
    float backgroundBottom = -backgroundTop;
    
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
    
    const GLfloat backgroundVertices[18] = { backgroundLeft,  backgroundTop,    0.0f,
                                             backgroundLeft,  backgroundBottom, 0.0f,
                                             backgroundRight, backgroundTop,    0.0f,

                                             backgroundLeft,  backgroundBottom, 0.0f,
                                             backgroundRight, backgroundBottom, 0.0f,
                                             backgroundRight, backgroundTop,    0.0f
    };
    
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    
    glColor4f(backgroundColor_.x, backgroundColor_.y, backgroundColor_.z, backgroundAlpha_);
    glVertexPointer(3, GL_FLOAT, 0, backgroundVertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 6);
     
    glEnable(GL_TEXTURE_2D);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    currentColorIndex_ = 1u;
    SetColor(0u);
    float x           = left;
    float y           = top;
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

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
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
            case 5u:
                color = Vector<float>(0.5f, 0.5f, 1.0f);
                break;
            default:
                break;
        }
        glColor4f(color.x, color.y, color.z, 1.0f);

        currentColorIndex_ = colorIndex;
    }
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

