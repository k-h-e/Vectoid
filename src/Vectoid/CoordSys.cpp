//
//  CoordSys.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Vectoid/CoordSys.h>

#include <kxm/Vectoid/OpenGL.h>


namespace kxm {
namespace Vectoid {

CoordSys::CoordSys() {
}

void CoordSys::Render(RenderContext *context) {
    glPushMatrix();
    glMultMatrixf(transform_.MatrixElements());
    CoordSysCore::Render(context);
    glPopMatrix();
}

}    // Namespace Vectoid.
}    // Namespace kxm.
