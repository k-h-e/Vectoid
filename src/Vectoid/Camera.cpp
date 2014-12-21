//
//  Camera.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <Vectoid/Camera.h>

#include <Vectoid/OpenGL.h>


namespace kxm {
namespace Vectoid {

Camera::Camera() {
}

void Camera::Render(RenderContext *context) {
    Transform inverse(Transform::InitAsInverse, transform_);
    glLoadIdentity();
    glMultMatrixf(inverse.MatrixElements());
    CoordSysCore::Render(context);
}

}    // Namespace Vectoid.
}    // Namespace kxm.
