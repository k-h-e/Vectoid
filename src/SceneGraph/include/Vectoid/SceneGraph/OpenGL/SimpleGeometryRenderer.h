///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_SIMPLEGEOMETRYRENDERER_H_
#define VECTOID_SCENEGRAPH_OPENGL_SIMPLEGEOMETRYRENDERER_H_

#include <vector>
#include <Vectoid/SceneGraph/SimpleGeometryRenderer.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! Renders simple geometry.
class SimpleGeometryRenderer : public SceneGraph::SimpleGeometryRenderer {
  public:
    SimpleGeometryRenderer()                                               = delete;
    SimpleGeometryRenderer(const std::shared_ptr<Context> &context, const std::shared_ptr<SimpleGeometry> &geometry);
    SimpleGeometryRenderer(const SimpleGeometryRenderer &other)            = delete;
    SimpleGeometryRenderer &operator=(const SimpleGeometryRenderer &other) = delete;
    SimpleGeometryRenderer(SimpleGeometryRenderer &&other)                 = delete;
    SimpleGeometryRenderer &operator=(SimpleGeometryRenderer &&other)      = delete;

    void Render() override;
    
  private:
    int                  numTriangles_;
    std::vector<GLfloat> vertexArray_,
                         colorArray_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_SIMPLEGEOMETRYRENDERER_H_
