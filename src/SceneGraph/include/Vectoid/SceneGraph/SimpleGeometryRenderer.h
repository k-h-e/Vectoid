///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_SIMPLEGEOMETRYRENDERER_H_
#define VECTOID_SCENEGRAPH_SIMPLEGEOMETRYRENDERER_H_

#include <memory>
#include <Vectoid/SceneGraph/Geometry.h>

namespace Vectoid {
namespace SceneGraph {

class SimpleGeometry;

//! Renders simple geometry.
class SimpleGeometryRenderer : public Geometry {
  public:
    SimpleGeometryRenderer()                                               = delete;
    SimpleGeometryRenderer(const SimpleGeometryRenderer &other)            = delete;
    SimpleGeometryRenderer &operator=(const SimpleGeometryRenderer &other) = delete;
    SimpleGeometryRenderer(SimpleGeometryRenderer &&other)                 = delete;
    SimpleGeometryRenderer &operator=(SimpleGeometryRenderer &&other)      = delete;
    
  protected:
    SimpleGeometryRenderer(const std::shared_ptr<Context> &context, const std::shared_ptr<SimpleGeometry> &geometry);

    std::shared_ptr<SimpleGeometry> geometry_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_SIMPLEGEOMETRYRENDERER_H_
