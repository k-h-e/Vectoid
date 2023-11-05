///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_TRANSPARENTTRIANGLES_H_
#define VECTOID_SCENEGRAPH_OPENGL_TRANSPARENTTRIANGLES_H_

#include <Vectoid/SceneGraph/TransparentTriangles.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! Renders transparent triangles.
class TransparentTriangles : public Vectoid::SceneGraph::TransparentTriangles {
  public:
    TransparentTriangles()                                             = delete;
    TransparentTriangles(const std::shared_ptr<Context> &context,
                         const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);
    TransparentTriangles(const TransparentTriangles &other)            = delete;
    TransparentTriangles &operator=(const TransparentTriangles &other) = delete;
    TransparentTriangles(TransparentTriangles &&other)                 = delete;
    TransparentTriangles &operator=(TransparentTriangles &&other)      = delete;
    ~TransparentTriangles();

    void Render() override;

  private:
    Context *Context() { return static_cast<class Context *>(context_.get()); }
    std::optional<GLuint> GenerateVBO();

    int vboSlot_;
    int numTriangles_;    // Valid <=> VBO present.
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_TRANSPARENTTRIANGLES_H_
