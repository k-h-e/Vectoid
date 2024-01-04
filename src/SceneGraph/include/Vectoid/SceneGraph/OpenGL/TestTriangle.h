///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_TESTTRIANGLE_H_
#define VECTOID_SCENEGRAPH_OPENGL_TESTTRIANGLE_H_

#include <Vectoid/SceneGraph/TestTriangle.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! Simple triangle geometry for testing purposes.
class TestTriangle : public Vectoid::SceneGraph::TestTriangle {
  public:
    TestTriangle()                                     = delete;
    TestTriangle(const std::shared_ptr<Context> &context);
    TestTriangle(const TestTriangle &other)            = delete;
    TestTriangle &operator=(const TestTriangle &other) = delete;
    TestTriangle(TestTriangle &&other)                 = delete;
    TestTriangle &operator=(TestTriangle &&other)      = delete;

    void Render() override;
    
  private:  
    static const GLfloat vertices[9];
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_TESTTRIANGLE_H_
