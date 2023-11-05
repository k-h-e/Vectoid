///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_PERSPECTIVEPROJECTION_H_
#define VECTOID_SCENEGRAPH_OPENGL_PERSPECTIVEPROJECTION_H_

#include <Vectoid/SceneGraph/PerspectiveProjection.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! Perspective screen projection, defining a frustum-shaped viewing volume.
class PerspectiveProjection : public Vectoid::SceneGraph::PerspectiveProjection {
  public:
    PerspectiveProjection()                                              = delete;
    PerspectiveProjection(const std::shared_ptr<Context> &context);
    PerspectiveProjection(const PerspectiveProjection &other)            = delete;
    PerspectiveProjection &operator=(const PerspectiveProjection &other) = delete;
    PerspectiveProjection(PerspectiveProjection &&other)                 = delete;
    PerspectiveProjection &operator=(PerspectiveProjection &&other)      = delete;

    void RenderPre() override; 
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_PERSPECTIVEPROJECTION_H_
