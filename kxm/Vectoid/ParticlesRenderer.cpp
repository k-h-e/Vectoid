//
//  ThrusterParticlesGeometry.cpp
//  kxm
//
//  Created by Kai Hergenroether on 5/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Vectoid/ParticlesRenderer.h>

#include <kxm/Vectoid/Particles.h>

using std::vector;
using boost::shared_ptr;
using namespace kxm::Core;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

ParticlesRenderer::ParticlesRenderer(shared_ptr<Particles> particles)
        : particles_(particles) {
}

void ParticlesRenderer::Render(RenderContext *context) {
    int num = particles_->Count();
    if (num == 0)
        return;
    if (num > (int)vertexBuffer_.size() / 3)
        vertexBuffer_.resize(num * 3);
        // See to it we have enough buffer space for all particles. The whole space might not be
        // needed, though, as particles can be hidden.
    
    GLfloat *ptr        = &vertexBuffer_[0];
    int     numToRender = 0;
    ItemGroups<Particles::ParticleInfo>::Iterator iter = particles_->GetIterator();
    Particles::ParticleInfo *particle;
    while ((particle = iter.GetNext())) {
        if (particle->hidden)
            continue;
        *ptr++ = particle->position.x;
        *ptr++ = particle->position.y;
        *ptr++ = particle->position.z;
        numToRender++;
    }
    
    if (numToRender) {
        glPointSize(3.0f);
        glVertexPointer(3, GL_FLOAT, 0, &vertexBuffer_[0]);
   	    glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_POINTS, 0, numToRender);
        glDisableClientState(GL_VERTEX_ARRAY);
        glPointSize(1.0f);
    }
}


}    // Namespace Zarch.
}    // Namespace kxm.
