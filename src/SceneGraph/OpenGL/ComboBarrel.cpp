///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/OpenGL/ComboBarrel.h>

#include <K/Core/NumberTools.h>
#include <Vectoid/Core/Transform.h>
#include <Vectoid/SceneGraph/Glyphs.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>

using std::shared_ptr;
using std::string;
using K::Core::NumberTools;
using Vectoid::Core::Transform;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

ComboBarrel::ComboBarrel(const shared_ptr<Context> &context, int width, int numVisibleOtherPerSide, float glyphWidth,
                         float glyphHeight, const shared_ptr<SceneGraph::Glyphs> &glyphs)
        : SceneGraph::ComboBarrel(context, width, numVisibleOtherPerSide, glyphWidth, glyphHeight, glyphs) {
    // Nop.
}

void ComboBarrel::Render() {
    float left = -.5f * width_ * glyphWidth_;
    
    int   positionInteger    = (position_ >= 0.0f) ? static_cast<int>(position_) : static_cast<int>(position_) - 1;
    float positionFractional = position_ - static_cast<float>(positionInteger);
    
    Vector<float> unselectedColor = .6f * color_;
    
    GLfloat vertices[]  = { boundingBox_.MinCorner().x,  boundingBox_.MaxCorner().y, 0.0f,
                            boundingBox_.MinCorner().x,  boundingBox_.MinCorner().y, 0.0f,
                            boundingBox_.MaxCorner().x,  boundingBox_.MaxCorner().y, 0.0f,

                            boundingBox_.MinCorner().x,  boundingBox_.MinCorner().y, 0.0f,
                            boundingBox_.MaxCorner().x,  boundingBox_.MinCorner().y, 0.0f,
                            boundingBox_.MaxCorner().x,  boundingBox_.MaxCorner().y, 0.0f  };
    
    GLfloat texCoords[] = { 0.0f, 0.0f,
                            1.0f, 0.0f,
                            1.0f, 1.0f,
                            
                            0.0f, 0.0f,
                            1.0f, 1.0f,
                            0.0f, 1.0f  };
    
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    
    glColor4f(backgroundColor_.x, backgroundColor_.y, backgroundColor_.z, backgroundAlpha_);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glEnable(GL_TEXTURE_2D);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    //glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    if (!items_.empty()) {
        glColor4f(unselectedColor.x, unselectedColor.y, unselectedColor.z, 1.0f);
        
        Transform<float> transform(Core::Axis::X, -positionFractional * itemAngle_);
        int   selection = *Selection();
        int   item      = positionInteger - numVisibleOtherPerSide_;
        for (int row = 0; row <= 2*numVisibleOtherPerSide_ + 1; ++row) {
            Vector<float> current{0.0f, yCoords_[row], zCoords_[row]};
            Vector<float> next{0.0f, yCoords_[row + 1], zCoords_[row + 1]};
            transform.ApplyTo(&current);
            transform.ApplyTo(&next);
            
            float y     = current.y;
            float nextY = next.y;
            float x     = left;
            
            if ((item >= 0) && (item < static_cast<int>(items_.size()))) {
                if (item == selection) {
                    glColor4f(color_.x, color_.y, color_.z, 1.0f);
                }
                
                string &itemText = items_[item];
                for (int col = 0; (col < width_) && (col < static_cast<int>(itemText.length())); ++col) {
                    float nextX = x + glyphWidth_;
                    char *ptr = &itemText[col];
                    if (*ptr != ' ') {
                        SetupRectangle(x, y, nextX, nextY, &vertices[0]);
                        glyphs_->BindGlyphTexture(*ptr);
                        glDrawArrays(GL_TRIANGLES, 0, 6);
                    }
                    x = nextX;
                }
                
                if (item == selection) {
                    glColor4f(unselectedColor.x, unselectedColor.y, unselectedColor.z, 1.0f);
                }
            }
            
            ++item;
        }
    }

    glColor4f(unselectedColor.x, unselectedColor.y, unselectedColor.z, 1.0f);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
    
    if (frameEnabled_) {
        //SetColor(static_cast<uint8_t>(frameColor_));
        SetupRectangle(boundingBox_.MinCorner().x - frameWidth_, boundingBox_.MaxCorner().y + frameWidth_,
                       boundingBox_.MaxCorner().x + frameWidth_, boundingBox_.MaxCorner().y, &vertices[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        SetupRectangle(boundingBox_.MinCorner().x - frameWidth_, boundingBox_.MinCorner().y,
                       boundingBox_.MaxCorner().x + frameWidth_, boundingBox_.MinCorner().y - frameWidth_,
                       &vertices[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        SetupRectangle(boundingBox_.MinCorner().x - frameWidth_, boundingBox_.MaxCorner().y,
                       boundingBox_.MinCorner().x, boundingBox_.MinCorner().y, &vertices[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        SetupRectangle(boundingBox_.MaxCorner().x, boundingBox_.MaxCorner().y,
                       boundingBox_.MaxCorner().x + frameWidth_, boundingBox_.MinCorner().y, &vertices[0]);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }
    
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glDisableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_DEPTH_TEST);
}

void ComboBarrel::SetupRectangle(float left, float top, float right, float bottom, GLfloat *outVertices) {
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
