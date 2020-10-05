#ifndef VECTOID_SCENEGRAPH_GEOMETRYINTERFACE_H_
#define VECTOID_SCENEGRAPH_GEOMETRYINTERFACE_H_

#include <K/Core/Interface.h>

namespace Vectoid {
namespace SceneGraph {

//! Interface to entities representing actual geometry.
class GeometryInterface : public virtual K::Core::Interface {
  public:
    //! Renders the geometry.
    virtual void Render() = 0;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_GEOMETRYINTERFACE_H_
