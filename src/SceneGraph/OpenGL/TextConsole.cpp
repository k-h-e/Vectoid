///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/OpenGL/TextConsole.h>

#include <string>
#include <cassert>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/Glyphs.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>

using std::shared_ptr;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

TextConsole::TextConsole(const shared_ptr<Context> &context, int width, int height, float glyphWidth, float glyphHeight,
                         const shared_ptr<SceneGraph::Glyphs> &glyphs)
        : SceneGraph::TextConsole{context, width, height, glyphWidth, glyphHeight, glyphs},
          currentColorIndex_{0u} {
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
    
    glEnableClientState(GL_VERTEX_ARRAY);
    if (backgroundEnabled_) {
        glColor4f(backgroundColor_.x, backgroundColor_.y, backgroundColor_.z, backgroundAlpha_);
        glVertexPointer(3, GL_FLOAT, 0, backgroundVertices);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
     
    glEnable(GL_TEXTURE_2D);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    currentColorIndex_ = 1u;
    SetColor(0u);
    float x           { left };
    float y           { top };
    uint8_t *ptr      { &buffer_[0] };
    uint8_t *colorPtr { &colorBuffer_[0] };
    for (int row = 0; row < height_; ++row) {
        float nextY { y - glyphHeight_ };
        for (int col = 0; col < width_; ++col) {
            float nextX { x + glyphWidth_ };
            if (*ptr != ' ') {
                SetupRectangle(x, y, nextX, nextY, &vertices[0]);
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

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    
    if (frameEnabled_) {
        glColor4f(frameColor_.x, frameColor_.y, frameColor_.z, 1.0f);
        SetupRectangle(backgroundLeft - frameWidth_, backgroundTop + frameWidth_,
                       backgroundRight + frameWidth_, backgroundTop, &vertices[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        SetupRectangle(backgroundLeft - frameWidth_, backgroundBottom,
                       backgroundRight + frameWidth_, backgroundBottom - frameWidth_, &vertices[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        SetupRectangle(backgroundLeft - frameWidth_, backgroundTop, backgroundLeft, backgroundBottom, &vertices[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        SetupRectangle(backgroundRight, backgroundTop, backgroundRight + frameWidth_, backgroundBottom, &vertices[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glDisableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_DEPTH_TEST);
}

void TextConsole::SetColor(uint8_t colorIndex) {
    if (colorIndex != currentColorIndex_) {
        Vector<float> color;
        switch (static_cast<Color>(colorIndex)) {
            case Color::White:
                color = Vector<float>(1.0f, 1.0f, 1.0f);
                break;
            case Color::Grey:
                color = Vector<float>(0.6f, 0.6f, 0.6f);
                break;
            case Color::Green:
                color = Vector<float>(0.0f, 1.0f, 0.0f);
                break;
            case Color::Yellow:
                color = Vector<float>(1.0f, 1.0f, 0.0f);
                break;
            case Color::Red:
                color = Vector<float>(1.0f, 0.0f, 0.0f);
                break;
            case Color::LightBlue:
                color = Vector<float>(0.5f, 0.5f, 1.0f);
                break;
            case Color::Custom:
                color = customColor_;
                break;
            default:
                break;
        }
        
        glColor4f(color.x, color.y, color.z, 1.0f);

        currentColorIndex_ = colorIndex;
    }
}

void TextConsole::SetupRectangle(float left, float top, float right, float bottom, GLfloat *outVertices) {
    outVertices[ 0] = left;     outVertices[ 1] = bottom;
    outVertices[ 3] = right;    outVertices[ 4] = bottom;
    outVertices[ 6] = right;    outVertices[ 7] = top;

    outVertices[ 9] = left;     outVertices[10] = bottom;
    outVertices[12] = right;    outVertices[13] = top;
    outVertices[15] = left;     outVertices[16] = top;
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

