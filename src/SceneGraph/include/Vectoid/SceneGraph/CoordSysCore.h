#ifndef VECTOID_SCENEGRAPH_COORDSYSCORE_H_
#define VECTOID_SCENEGRAPH_COORDSYSCORE_H_

#include <Vectoid/Core/Transform.h>
#include <Vectoid/SceneGraph/SceneGraphNode.h>
#include <Vectoid/SceneGraph/CoordSysInterface.h>

namespace Vectoid {
namespace SceneGraph {

//! Base class for scene graph nodes implementing \ref CoordSysInterface.
/*! 
 *  \ingroup Vectoid
 */ 
class CoordSysCore : public SceneGraphNode,
                     public virtual CoordSysInterface {
  public:
    CoordSysCore();
    void PrependTransform(const Core::Transform<float> &other);
    void AppendTransform(const Core::Transform<float> &other);
    void SetTransform(const Core::Transform<float> &other);
    void GetTransform(Core::Transform<float> *outTransform) const;
    void SetPosition(const Core::Vector<float> &pos);
    void GetPosition(Core::Vector<float> *outPos);
    Core::Vector<float> Position();
    
  protected:
    Core::Transform<float> transform_;
    bool                   transformChanged_;
    
  private:
    CoordSysCore(const CoordSysCore &other);
    CoordSysCore &operator=(const CoordSysCore &other);
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_COORDSYSCORE_H_
