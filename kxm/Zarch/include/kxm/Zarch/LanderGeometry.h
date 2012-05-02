//
//  LanderGeometry.h
//  kxm
//
//  Created by Kai Hergenroether on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_LANDERGEOMETRY_H_
#define KXM_ZARCH_LANDERGEOMETRY_H_


#include <kxm/Vectoid/OpenGL.h>
#include <kxm/Vectoid/GeometryInterface.h>


namespace kxm {

namespace Vectoid {
    class RenderContext;
}

namespace Zarch {

//! Initial, simple geometry for the lander (the vehicle controlled by the player).
/*!
 *  \ingroup Zarch
 */
class LanderGeometry : public virtual Vectoid::GeometryInterface {
  public:
    LanderGeometry();
    
    void Render(Vectoid::RenderContext *context);
    
  private:
    LanderGeometry(const LanderGeometry &other);
    LanderGeometry &operator=(const LanderGeometry &other);
    
    GLfloat vertices_[9];
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_LANDERGEOMETRY_H_
