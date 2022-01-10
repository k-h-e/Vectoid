#ifndef VECTOID_SCENEGRAPH_LITCOLORCODEDTRIANGLES_H_
#define VECTOID_SCENEGRAPH_LITCOLORCODEDTRIANGLES_H_

#include <memory>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/GeometryInterface.h>

namespace Vectoid {
namespace Core {
    class TriangleProviderInterface;
}
}

namespace Vectoid {
namespace SceneGraph {

//! Renders lit, color-coded triangles (useful e.g. for depth maps).
class LitColorCodedTriangles : public virtual GeometryInterface {
  public:
    LitColorCodedTriangles(const LitColorCodedTriangles &other)            = delete;
    LitColorCodedTriangles &operator=(const LitColorCodedTriangles &other) = delete;
    LitColorCodedTriangles(LitColorCodedTriangles &&other)                 = delete;
    LitColorCodedTriangles &operator=(LitColorCodedTriangles &&other)      = delete;
    //! Sets a color coding function. Pass empty function to unset.
    void SetColorCodingFunction(
        const std::function<Vectoid::Core::Vector<float>(const Vectoid::Core::Vector<float> &)> &colorCodingFunction);
    //! Switches Gouraud shading on and off.
    virtual void EnableGouraudShading(bool enabled) = 0;

  protected:
    LitColorCodedTriangles(const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider);

    std::shared_ptr<Core::TriangleProviderInterface>                                  triangleProvider_;
    std::function<Vectoid::Core::Vector<float>(const Vectoid::Core::Vector<float> &)> colorCodingFunction_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_LITCOLORCODEDTRIANGLES_H_
