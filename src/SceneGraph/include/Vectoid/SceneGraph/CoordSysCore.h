#ifndef VECTOID_SCENEGRAPH_COORDSYSCORE_H_
#define VECTOID_SCENEGRAPH_COORDSYSCORE_H_

#include <Vectoid/Core/Transform.h>
#include <Vectoid/SceneGraph/GroupNode.h>
#include <Vectoid/SceneGraph/CoordSysInterface.h>

namespace Vectoid {
namespace SceneGraph {

//! Base class for scene graph nodes implementing \ref CoordSysInterface.
class CoordSysCore : public GroupNode,
                     public virtual CoordSysInterface {
  public:
    CoordSysCore()                                     = delete;
    CoordSysCore(const CoordSysCore &other)            = delete;
    CoordSysCore &operator=(const CoordSysCore &other) = delete;
    CoordSysCore(CoordSysCore &&other)                 = delete;
    CoordSysCore &operator=(CoordSysCore &&other)      = delete;

    void PrependTransform(const Core::Transform<float> &other);
    void AppendTransform(const Core::Transform<float> &other);
    void SetTransform(const Core::Transform<float> &other);
    void GetTransform(Core::Transform<float> *outTransform) const;
    void SetPosition(const Core::Vector<float> &pos);
    void GetPosition(Core::Vector<float> *outPos);
    Core::Vector<float> Position();
    
  protected:
    CoordSysCore(const std::shared_ptr<Context> &context);

    Core::Transform<float> transform_;
    bool                   transformChanged_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_COORDSYSCORE_H_
