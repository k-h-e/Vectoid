#include "Indicatower.h"

using namespace kxm::Vectoid;


namespace Raspiator {

const GLfloat Indicatower::normals[90] = {
     0.0f, 0.0f,  1.0f,     0.0f, 0.0f,  1.0f,     0.0f, 0.0f,  1.0f,
     0.0f, 0.0f,  1.0f,     0.0f, 0.0f,  1.0f,     0.0f, 0.0f,  1.0f,
     
     0.0f, 0.0f, -1.0f,     0.0f, 0.0f, -1.0f,     0.0f, 0.0f, -1.0f,
     0.0f, 0.0f, -1.0f,     0.0f, 0.0f, -1.0f,     0.0f, 0.0f, -1.0f,
     
    -1.0f, 0.0f,  0.0f,    -1.0f, 0.0f,  0.0f,    -1.0f, 0.0f,  0.0f,
    -1.0f, 0.0f,  0.0f,    -1.0f, 0.0f,  0.0f,    -1.0f, 0.0f,  0.0f,
    
     1.0f, 0.0f,  0.0f,     1.0f, 0.0f,  0.0f,     1.0f, 0.0f,  0.0f,
     1.0f, 0.0f,  0.0f,     1.0f, 0.0f,  0.0f,     1.0f, 0.0f,  0.0f,
     
     0.0f, 1.0f,  0.0f,     0.0f, 1.0f,  0.0f,     0.0f, 1.0f,  0.0f,
     0.0f, 1.0f,  0.0f,     0.0f, 1.0f,  0.0f,     0.0f, 1.0f,  0.0f
};

Indicatower::Indicatower() {
    color_[0] = .8f;    color_[1] = .8f;    color_[2] = .2f;    color_[3] = 1.0f;
    SetHeight(.2f);
}

void Indicatower::SetHeight(float height) {
    GLfloat *ptr = vertices_;
    
    *ptr++ = -1.0f;    *ptr++ = 0.0f;      *ptr++ =  1.0f;
    *ptr++ =  1.0f;    *ptr++ = 0.0f;      *ptr++ =  1.0f;
    *ptr++ = -1.0f;    *ptr++ = height;    *ptr++ =  1.0f;
    
    *ptr++ =  1.0f;    *ptr++ = 0.0f;      *ptr++ =  1.0f;
    *ptr++ =  1.0f;    *ptr++ = height;    *ptr++ =  1.0f;
    *ptr++ = -1.0f;    *ptr++ = height;    *ptr++ =  1.0f;
    
    *ptr++ = -1.0f;    *ptr++ = 0.0f;      *ptr++ = -1.0f;
    *ptr++ = -1.0f;    *ptr++ = height;    *ptr++ = -1.0f;
    *ptr++ =  1.0f;    *ptr++ = 0.0f;      *ptr++ = -1.0f;
    
    *ptr++ =  1.0f;    *ptr++ = 0.0f;      *ptr++ = -1.0f;
    *ptr++ = -1.0f;    *ptr++ = height;    *ptr++ = -1.0f;
    *ptr++ =  1.0f;    *ptr++ = height;    *ptr++ = -1.0f;
    
    *ptr++ = -1.0f;    *ptr++ = 0.0f;      *ptr++ = -1.0f;
    *ptr++ = -1.0f;    *ptr++ = 0.0f;      *ptr++ =  1.0f;
    *ptr++ = -1.0f;    *ptr++ = height;    *ptr++ =  1.0f;
    
    *ptr++ = -1.0f;    *ptr++ = 0.0f;      *ptr++ = -1.0f;
    *ptr++ = -1.0f;    *ptr++ = height;    *ptr++ =  1.0f;
    *ptr++ = -1.0f;    *ptr++ = height;    *ptr++ = -1.0f;
    
    *ptr++ =  1.0f;    *ptr++ = 0.0f;      *ptr++ = -1.0f;
    *ptr++ =  1.0f;    *ptr++ = height;    *ptr++ =  1.0f;
    *ptr++ =  1.0f;    *ptr++ = 0.0f;      *ptr++ =  1.0f;
    
    *ptr++ =  1.0f;    *ptr++ = 0.0f;      *ptr++ = -1.0f;
    *ptr++ =  1.0f;    *ptr++ = height;    *ptr++ = -1.0f;
    *ptr++ =  1.0f;    *ptr++ = height;    *ptr++ =  1.0f;
    
    *ptr++ = -1.0f;    *ptr++ = height;    *ptr++ =  1.0f;
    *ptr++ =  1.0f;    *ptr++ = height;    *ptr++ =  1.0f;
    *ptr++ =  1.0f;    *ptr++ = height;    *ptr++ = -1.0f;
    
    *ptr++ = -1.0f;    *ptr++ = height;    *ptr++ =  1.0f;
    *ptr++ =  1.0f;    *ptr++ = height;    *ptr++ = -1.0f;
    *ptr++ = -1.0f;    *ptr++ = height;    *ptr++ = -1.0f;
}

void Indicatower::Render(RenderContext *context) {
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color_);
    glEnable(GL_LIGHTING);
    glVertexPointer(3, GL_FLOAT, 0, vertices_);
    glNormalPointer(GL_FLOAT, 0, normals);
   	glEnableClientState(GL_VERTEX_ARRAY);
   	glEnableClientState(GL_NORMAL_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 30);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisable(GL_LIGHTING);
}

}    // Namespace Raspiator.

