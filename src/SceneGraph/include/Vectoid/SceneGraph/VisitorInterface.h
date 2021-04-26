#ifndef VECTOID_SCENEGRAPH_VISITORINTERFACE_H_
#define VECTOID_SCENEGRAPH_VISITORINTERFACE_H_

#include <K/Core/Interface.h>

namespace Vectoid {
namespace SceneGraph {

class Camera;
class CoordSys;
class Geode;
class PerspectiveProjection;
class SimpleLighting;

//! Interface to scene graph visitors.
class VisitorInterface : public virtual K::Core::Interface {
  public:
    virtual void Visit(::Vectoid::SceneGraph::Camera *camera) = 0;
    virtual void Leave(::Vectoid::SceneGraph::Camera *camera) = 0;
    virtual void Visit(::Vectoid::SceneGraph::CoordSys *coordSys) = 0;
    virtual void Leave(::Vectoid::SceneGraph::CoordSys *coordSys) = 0;
    virtual void Visit(::Vectoid::SceneGraph::Geode *geode) = 0;
    virtual void Leave(::Vectoid::SceneGraph::Geode *geode) = 0;
    virtual void Visit(::Vectoid::SceneGraph::PerspectiveProjection *perspectiveProjection) = 0;
    virtual void Leave(::Vectoid::SceneGraph::PerspectiveProjection *perspectiveProjection) = 0;
    virtual void Visit(::Vectoid::SceneGraph::SimpleLighting *simpleLighting) = 0;
    virtual void Leave(::Vectoid::SceneGraph::SimpleLighting *simpleLighting) = 0;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VISITORINTERFACE_H_

