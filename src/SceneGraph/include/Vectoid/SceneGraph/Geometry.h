///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_GEOMETRY_H_
#define VECTOID_SCENEGRAPH_GEOMETRY_H_

#include <Vectoid/SceneGraph/Node.h>

namespace Vectoid {
namespace SceneGraph {

//! Base class to scene graph nodes representing actual geometry.
class Geometry : public Node {
  public:
    Geometry()                                 = delete;
    Geometry(const std::shared_ptr<Context> &context);
    Geometry(const Geometry &other)            = delete;
    Geometry &operator=(const Geometry &other) = delete;
    Geometry(Geometry &&other)                 = delete;
    Geometry &operator=(Geometry &&other)      = delete;

    //! Renders the geometry.
    virtual void Render() = 0;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_GEOMETRY_H_
