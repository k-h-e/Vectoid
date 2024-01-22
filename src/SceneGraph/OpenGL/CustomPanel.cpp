///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/OpenGL/CustomPanel.h>

#include <Vectoid/SceneGraph/OpenGL/Context.h>

using std::shared_ptr;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

CustomPanel::CustomPanel(const shared_ptr<Context> &context, float width, float height)
        : SceneGraph::CustomPanel{context, width, height} {
    // Nop.
}

void CustomPanel::Render() {
    float left             = -.5f * width_;
    float top              =  .5f * height_;
    float backgroundLeft   = left;
    float backgroundRight  = -backgroundLeft;
    float backgroundTop    = top;
    float backgroundBottom = -backgroundTop;
    
    GLfloat vertices[18] = { backgroundLeft,  backgroundTop,    0.0f,
                             backgroundLeft,  backgroundBottom, 0.0f,
                             backgroundRight, backgroundTop,    0.0f,

                             backgroundLeft,  backgroundBottom, 0.0f,
                             backgroundRight, backgroundBottom, 0.0f,
                             backgroundRight, backgroundTop,    0.0f
    };
    
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    
    glColor4f(backgroundColor_.x, backgroundColor_.y, backgroundColor_.z, backgroundAlpha_);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 6);

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

    glDisableClientState(GL_VERTEX_ARRAY);
    glEnable(GL_DEPTH_TEST);

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void CustomPanel::SetupRectangle(float left, float top, float right, float bottom, GLfloat *outVertices) {
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
