//
//  Camera.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Vectoid/Camera.h>

#include <kxm/Vectoid/OpenGL.h>


namespace kxm {
namespace Vectoid {

Camera::Camera() {
}

void Camera::Render(RenderContext *context) {
    Transform inverse(Transform::InitAsInverseRotation, transform_);
    glLoadIdentity();
    glMultMatrixf(inverse.MatrixElements());
    CoordSysCore::Render(context);
}

}    // Namespace Vectoid.
}    // Namespace kxm.
