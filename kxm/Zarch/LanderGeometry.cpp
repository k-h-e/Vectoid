//
//  LanderGeometry.cpp
//  kxm
//
//  Created by Kai Hergenroether on 5/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/LanderGeometry.h>

using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

LanderGeometry::LanderGeometry() {
}

void LanderGeometry::Render(RenderContext *context) {
    glVertexPointer(3, GL_FLOAT, 0, vertices_);
   	glEnableClientState(GL_VERTEX_ARRAY);
    
    glColor4f(.8f, .8f, .2f, 1.0f);
    vertices_[0] = -.5f;  vertices_[1] = 0.0f;   vertices_[2] =   .5f;
    vertices_[3] =  .5f;  vertices_[4] = 0.0f;   vertices_[5] =   .5f;
    vertices_[6] = 0.0f;  vertices_[7] = 0.0f;   vertices_[8] = -1.0f;
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vertices_[0] = -.5f;  vertices_[1] = 0.0f;   vertices_[2] =   .5f;
    vertices_[3] =  .5f;  vertices_[4] = 0.0f;   vertices_[5] =   .5f;
    vertices_[6] = 0.0f;  vertices_[7] = 0.35f;  vertices_[8] =  0.0f;
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glColor4f(.8f, .5f, .2f, 1.0f);
    vertices_[0] = - .5f;  vertices_[1] = 0.0f;   vertices_[2] =   .5f;
    vertices_[3] =  0.0f;  vertices_[4] = 0.5f;   vertices_[5] = - .8f;
    vertices_[6] =  0.0f;  vertices_[7] = 0.35f;  vertices_[8] =  0.0f;
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vertices_[0] =   .5f;  vertices_[1] = 0.0f;   vertices_[2] =   .5f;
    vertices_[3] =  0.0f;  vertices_[4] = 0.5f;   vertices_[5] = - .8f;
    vertices_[6] =  0.0f;  vertices_[7] = 0.35f;  vertices_[8] =  0.0f;
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glColor4f(.5f, .8f, .2f, 1.0f);
    vertices_[0] = - .5f;  vertices_[1] = 0.0f;  vertices_[2] =   .5f;
    vertices_[3] =  0.0f;  vertices_[4] = 0.5f;  vertices_[5] = - .8f;
    vertices_[6] = -1.0f;  vertices_[7] = 0.1f;  vertices_[8] = -1.0f;
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vertices_[0] =   .5f;  vertices_[1] = 0.0f;  vertices_[2] =   .5f;
    vertices_[3] =  0.0f;  vertices_[4] = 0.5f;  vertices_[5] = - .8f;
    vertices_[6] =  1.0f;  vertices_[7] = 0.1f;  vertices_[8] = -1.0f;
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glColor4f(.2f, .5f, .8f, 1.0f);
    vertices_[0] = - .5f;  vertices_[1] = 0.0f;  vertices_[2] =   .5f;
    vertices_[3] = -1.0f;  vertices_[4] = 0.1f;  vertices_[5] = -1.0f;
    vertices_[6] =  0.0f;  vertices_[7] = 0.0f;  vertices_[8] = -1.0f;
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vertices_[0] =   .5f;  vertices_[1] = 0.0f;  vertices_[2] =   .5f;
    vertices_[3] =  1.0f;  vertices_[4] = 0.1f;  vertices_[5] = -1.0f;
    vertices_[6] =  0.0f;  vertices_[7] = 0.0f;  vertices_[8] = -1.0f;
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glColor4f(.8f, .2f, .3f, 1.0f);
    vertices_[0] =  0.0f;  vertices_[1] = 0.5f;  vertices_[2] = - .8f;
    vertices_[3] = -1.0f;  vertices_[4] = 0.1f;  vertices_[5] = -1.0f;
    vertices_[6] =  0.0f;  vertices_[7] = 0.0f;  vertices_[8] = -1.0f;
    glDrawArrays(GL_TRIANGLES, 0, 3);
    vertices_[0] =  0.0f;  vertices_[1] = 0.5f;  vertices_[2] = - .8f;
    vertices_[3] =  1.0f;  vertices_[4] = 0.1f;  vertices_[5] = -1.0f;
    vertices_[6] =  0.0f;  vertices_[7] = 0.0f;  vertices_[8] = -1.0f;
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glDisableClientState(GL_VERTEX_ARRAY);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}


}    // Namespace Zarch.
}    // Namespace kxm.
