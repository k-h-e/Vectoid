///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_GEODE_H_
#define VECTOID_SCENEGRAPH_OPENGL_GEODE_H_

#include <Vectoid/SceneGraph/Geode.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! This scene graph node represents actual geometry in the scene (geode = geometry node).
class Geode : public Vectoid::SceneGraph::Geode {
  public:
    Geode()                              = delete;
    Geode(const std::shared_ptr<Context> &context, const std::shared_ptr<Geometry> &geometry);
    Geode(const Geode &other)            = delete;
    Geode &operator=(const Geode &other) = delete;
    Geode(Geode &&other)                 = delete;
    Geode &operator=(Geode &&other)      = delete;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.


#endif    // VECTOID_SCENEGRAPH_OPENGL_GEODE_H_
