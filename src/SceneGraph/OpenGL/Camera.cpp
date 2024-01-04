///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/OpenGL/Camera.h>

#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using std::shared_ptr;
using Vectoid::Core::Transform;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

Camera::Camera(const shared_ptr<Context> &context)
        : SceneGraph::Camera(context) {
    //Nop.
}

void Camera::RenderPre() {
    Transform<float> inverse(Transform<float>::InitAsInverse, transform_);
    glLoadIdentity();
    glMultMatrixf(inverse.MatrixElements());
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
