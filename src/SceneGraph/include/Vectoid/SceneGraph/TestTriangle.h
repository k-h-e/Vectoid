///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_TESTTRIANGLE_H_
#define VECTOID_SCENEGRAPH_TESTTRIANGLE_H_

#include <Vectoid/SceneGraph/Geometry.h>

namespace Vectoid {
namespace SceneGraph {

//! Simple triangle geometry for testing purposes.
class TestTriangle : public Geometry {
  public:
    TestTriangle()                                     = delete;
    TestTriangle(const TestTriangle &other)            = delete;
    TestTriangle &operator=(const TestTriangle &other) = delete;
    TestTriangle(TestTriangle &&other)                 = delete;
    TestTriangle &operator=(TestTriangle &&other)      = delete;
    
  protected:
    TestTriangle(const std::shared_ptr<Context> &context);
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_TESTTRIANGLE_H_
