///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_COORDSYS_H_
#define VECTOID_SCENEGRAPH_COORDSYS_H_

#include <Vectoid/SceneGraph/CoordSysCore.h>

namespace Vectoid {
namespace SceneGraph {

//! This scene graph node sets up a local coordinate system for its children.
class CoordSys : public CoordSysCore {
  public:
    CoordSys()                                 = delete;
    CoordSys(const CoordSys &other)            = delete;
    CoordSys &operator=(const CoordSys &other) = delete;
    CoordSys(CoordSys &&other)                 = delete;
    CoordSys &operator=(CoordSys &&other)      = delete;

  protected:
    CoordSys(const std::shared_ptr<Context> &context);
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_COORDSYS_H_
