//
//  CoordSysCore.h
//  kxm
//
//  Created by Kai Hergenroether on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_VECTOID_COORDSYSCORE_H_
#define KXM_VECTOID_COORDSYSCORE_H_


#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/SceneGraphNode.h>
#include <kxm/Vectoid/CoordSysInterface.h>


namespace kxm {
namespace Vectoid {

//! Base class for scene graph nodes implementing \ref CoordSysInterface.
/*! 
 *  \ingroup Vectoid
 */ 
class CoordSysCore : public SceneGraphNode,
                     public virtual CoordSysInterface {
  public:
    CoordSysCore();
    void PrependTransform(const Transform &other);
    void AppendTransform(const Transform &other);
    void SetTransform(const Transform &other);
    void GetTransform(Transform *outTransform) const;
    void SetPosition(const Vector &pos);
    void GetPosition(Vector *outPos);
    Vector Position();
    
  protected:
    Transform transform_;
    bool      transformChanged_;
    
  private:
    CoordSysCore(const CoordSysCore &other);
    CoordSysCore &operator=(const CoordSysCore &other);
};

}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_COORDSYSCORE_H_
