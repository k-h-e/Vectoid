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
     
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glDisableClientState(GL_VERTEX_ARRAY);
   
    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
