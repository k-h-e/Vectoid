#ifndef VECTOID_SCENEGRAPH_OPENGL_LITCOLORCODEDTRIANGLES_H_
#define VECTOID_SCENEGRAPH_OPENGL_LITCOLORCODEDTRIANGLES_H_


#include <memory>
#include <optional>
#include <vector>
#include <Vectoid/DataSet/Triangles.h>
#include <Vectoid/SceneGraph/LitColorCodedTriangles.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {

namespace SceneGraph {
namespace OpenGL {

//! Renders lit, color-coded triangles.
/*!
 *  \note
 *  For the time being, this implementation maintains its own geometry representation in the Gouraud case (as
 *  opposed to using OpenGL resources).
 */
class LitColorCodedTriangles : public Vectoid::SceneGraph::LitColorCodedTriangles {
  public:
    LitColorCodedTriangles(const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);
    LitColorCodedTriangles(const LitColorCodedTriangles &other)            = delete;
    LitColorCodedTriangles &operator=(const LitColorCodedTriangles &other) = delete;
    LitColorCodedTriangles(LitColorCodedTriangles &&other)                 = delete;
    LitColorCodedTriangles &operator=(LitColorCodedTriangles &&other)      = delete;
    void EnableGouraudShading(bool enabled) override;
    virtual void Render() override;

  private:
    void RenderFlat();
    void RenderGouraud();
    Vectoid::Core::Vector<float> GetColor(const Vectoid::Core::Vector<float> &vertex);
    void GenerateGouraudResources();

    std::optional<GLuint> vbo_;
    bool                  vboInvalid_;
    int                   numTriangles_;             // Valid <=> VBO present.
    bool                  gouraudShadingEnabled_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_LITCOLORCODEDTRIANGLES_H_
