#include "Indicatower.h"

using namespace kxm::Vectoid;


namespace Raspiator {

Indicatower::Indicatower() {
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
    glColor4f(.8f, .8f, .2f, 1.0f);
    glVertexPointer(3, GL_FLOAT, 0, vertices_);
   	glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_TRIANGLES, 0, 30);
    glDisableClientState(GL_VERTEX_ARRAY);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

}    // Namespace Raspiator.

