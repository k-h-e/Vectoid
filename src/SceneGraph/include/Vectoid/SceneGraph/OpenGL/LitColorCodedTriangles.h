///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_LITCOLORCODEDTRIANGLES_H_
#define VECTOID_SCENEGRAPH_OPENGL_LITCOLORCODEDTRIANGLES_H_

#include <memory>
#include <optional>
#include <vector>
#include <Vectoid/DataSet/Triangles.h>
#include <Vectoid/SceneGraph/LitColorCodedTriangles.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>

namespace Vectoid {

namespace SceneGraph {
namespace OpenGL {

class RenderTarget;

//! Renders lit, color-coded triangles.
/*!
 *  \note
 *  For the time being, this implementation maintains its own geometry representation in the Gouraud case (as
 *  opposed to using OpenGL resources).
 */
class LitColorCodedTriangles : public Vectoid::SceneGraph::LitColorCodedTriangles {
  public:
    LitColorCodedTriangles()                                               = delete;
    LitColorCodedTriangles(const std::shared_ptr<Context> &context,
                           const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);
    LitColorCodedTriangles(const LitColorCodedTriangles &other)            = delete;
    LitColorCodedTriangles &operator=(const LitColorCodedTriangles &other) = delete;
    LitColorCodedTriangles(LitColorCodedTriangles &&other)                 = delete;
    LitColorCodedTriangles &operator=(LitColorCodedTriangles &&other)      = delete;
    ~LitColorCodedTriangles();

    void Render() override;

  private:
    Context *Context() { return static_cast<class Context *>(context_.get()); }
    std::optional<GLuint> GenerateVBO();
    std::optional<GLuint> GenerateRegularVBO();
    std::optional<GLuint> GenerateGouraudVBO();
    Vectoid::Core::Vector<float> GetColor(const Vectoid::Core::Vector<float> &vertex);

    int  vboSlot_;
    int  numTriangles_;             // Valid <=> VBO present.
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_LITCOLORCODEDTRIANGLES_H_
