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
    
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    
    Transform<float> transform(Vector<float>(0.0f, 0.0f, -barrelRadius_));
    glPushMatrix();
    glMultMatrixf(transform.MatrixElements());
    
    glColor4f(backgroundColor_.x, backgroundColor_.y, backgroundColor_.z, backgroundAlpha_);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    
    for (int row = 0; row <= 2*numVisibleOtherPerSide_ + 1; ++row) {
        float y     = yCoords_[row];
        float nextY = yCoords_[row + 1];
        float z     = zCoords_[row];
        float nextZ = zCoords_[row + 1];
        float x     = left;
        float nextX = x + width_*glyphWidth_;
       
        vertices[ 0] = x;        vertices[ 1] = nextY;    vertices[ 2] = nextZ;
        vertices[ 3] = nextX;    vertices[ 4] = nextY;    vertices[ 5] = nextZ;
        vertices[ 6] = nextX;    vertices[ 7] = y;        vertices[ 8] = z;
        
        vertices[ 9] = x;        vertices[10] = nextY;    vertices[11] = nextZ;
        vertices[12] = nextX;    vertices[13] = y;        vertices[14] = z;
        vertices[15] = x;        vertices[16] = y;        vertices[17] = z;
        
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    glPopMatrix();
    transform = Transform<float>(Core::Axis::X, -positionFractional * itemAngle_);
    transform.Append(Transform<float>(Vector<float>(0.0f, 0.0f, -barrelRadius_)));
    glPushMatrix();
    glMultMatrixf(transform.MatrixElements());
    
    glEnable(GL_TEXTURE_2D);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords);
    //glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    if (!items_.empty()) {
        int   selection = *Selection();
        int   item      = positionInteger - numVisibleOtherPerSide_;
        for (int row = 0; row <= 2*numVisibleOtherPerSide_ + 1; ++row) {
            float y     = yCoords_[row];
            float nextY = yCoords_[row + 1];
            float z     = zCoords_[row];
            float nextZ = zCoords_[row + 1];
            float x     = left;
            
            if ((item >= 0) && (item < static_cast<int>(items_.size()))) {
                if (item == selection) {
                    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
                } else {
                    glColor4f(0.5f, 0.5f, 0.5f, 1.0f);
                }
                string &itemText = items_[item];
                for (int col = 0; (col < width_) && (col < static_cast<int>(itemText.length())); ++col) {
                    float nextX = x + glyphWidth_;
                    char *ptr = &itemText[col];
                    if (*ptr != ' ') {
                        vertices[ 0] = x;        vertices[ 1] = nextY;    vertices[ 2] = nextZ;
                        vertices[ 3] = nextX;    vertices[ 4] = nextY;    vertices[ 5] = nextZ;
                        vertices[ 6] = nextX;    vertices[ 7] = y;        vertices[ 8] = z;
                        
                        vertices[ 9] = x;        vertices[10] = nextY;    vertices[11] = nextZ;
                        vertices[12] = nextX;    vertices[13] = y;        vertices[14] = z;
                        vertices[15] = x;        vertices[16] = y;        vertices[17] = z;
                        
                        glyphs_->BindGlyphTexture(*ptr);
                        glDrawArrays(GL_TRIANGLES, 0, 6);
                    }
                    x = nextX;
                }
            }
            
            ++item;
        }
    }

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisable(GL_TEXTURE_2D);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
    
    glPopMatrix();
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
