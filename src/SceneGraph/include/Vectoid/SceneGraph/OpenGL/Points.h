///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_POINTS_H_
#define VECTOID_SCENEGRAPH_OPENGL_POINTS_H_

#include <optional>
#include <Vectoid/SceneGraph/Points.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! Renders points.
class Points : public Vectoid::SceneGraph::Points {
  public:
    Points()                               = delete;
    Points(const std::shared_ptr<Context> &context, const std::shared_ptr<DataSet::Points> &points);
    Points(const Points &other)            = delete;
    Points &operator=(const Points &other) = delete;
    Points(Points &&other)                 = delete;
    Points &operator=(Points &&other)      = delete;
    ~Points();

    void Render() override;

  private:
    Context *Context() { return static_cast<class Context *>(context_.get()); }
    std::optional<GLuint> GenerateVBO();

    int vboSlot_;
    int numPoints_;    // Valid <=> VBO present.
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_POINTS_H_
