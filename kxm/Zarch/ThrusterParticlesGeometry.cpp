//
//  ThrusterParticlesGeometry.cpp
//  kxm
//
//  Created by Kai Hergenroether on 5/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/ThrusterParticlesGeometry.h>

#include <kxm/Vectoid/Particles.h>

using std::vector;
using boost::shared_ptr;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

ThrusterParticlesGeometry::ThrusterParticlesGeometry(shared_ptr<Particles> particles)
        : particles_(particles) {
}

void ThrusterParticlesGeometry::Render(RenderContext *context) {
    int num = particles_->Count();
    if (num == 0)
        return;
    if (num > (int)vertexBuffer_.size() / 3)
        vertexBuffer_.resize(num * 3);
    GLfloat *ptr = &vertexBuffer_[0];
    Particles::Iterator iter = particles_->BeginIteration();
    Particles::ParticleInfo *particle;
    while ((particle = iter.Next())) {
        *ptr++ = particle->position.x;
        *ptr++ = particle->position.y;
        *ptr++ = particle->position.z;
    }
    glPointSize(3.0f);
    glVertexPointer(3, GL_FLOAT, 0, &vertexBuffer_[0]);
   	glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_POINTS, 0, num);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPointSize(1.0f);
}


}    // Namespace Zarch.
}    // Namespace kxm.
