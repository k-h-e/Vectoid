///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_SCALARGRID2D_H_
#define VECTOID_SCENEGRAPH_SCALARGRID2D_H_

#include <Vectoid/SceneGraph/Geometry.h>

namespace Vectoid {
    namespace SceneGraph {
        class Context;
    }
}

namespace Vectoid {
namespace SceneGraph {

//! Renders scalar data arranged in a 2D grid.
class ScalarGrid2D : public Geometry {
  public:
    ScalarGrid2D()                                     = delete;
    ScalarGrid2D(const ScalarGrid2D &other)            = delete;
    ScalarGrid2D &operator=(const ScalarGrid2D &other) = delete;
    ScalarGrid2D(ScalarGrid2D &&other)                 = delete;
    ScalarGrid2D &operator=(ScalarGrid2D &&other)      = delete;
    ~ScalarGrid2D()                                    = default;

  protected:
    ScalarGrid2D(const std::shared_ptr<Context> &context, float width, float height, int numColumns, int numRows);

    float width_;
    float height_;
    int   numColumns_;
    int   numRows_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_SCALARGRID2D_H_
