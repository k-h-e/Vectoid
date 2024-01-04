///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_SCALARGRID2D_H_
#define VECTOID_SCENEGRAPH_OPENGL_SCALARGRID2D_H_

#include <Vectoid/SceneGraph/ScalarGrid2D.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

//! Renders scalar data arranged in a 2D grid.
class ScalarGrid2D : public SceneGraph::ScalarGrid2D {
  public:
    ScalarGrid2D(const std::shared_ptr<SceneGraph::Context> &context, float width, float height, int numColumns,
                 int numRows);
    ScalarGrid2D()                                     = delete;
    ScalarGrid2D(const ScalarGrid2D &other)            = delete;
    ScalarGrid2D &operator=(const ScalarGrid2D &other) = delete;
    ScalarGrid2D(ScalarGrid2D &&other)                 = delete;
    ScalarGrid2D &operator=(ScalarGrid2D &&other)      = delete;
    ~ScalarGrid2D()                                    = default;

    void Render() override;

  private:
};

}    // Namespace OpenGL;
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_SCALARGRID2D_H_
