///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/OpenGL/AgeColoredParticles.h>

#include <K/Core/NumberTools.h>
#include <Vectoid/Core/Particles.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

using namespace std;
using K::Core::NumberTools;
using Vectoid::Core::Vector;
using Vectoid::Core::Particles;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

AgeColoredParticles::AgeColoredParticles(const shared_ptr<Context> &context, const shared_ptr<Particles> &particles)
        : SceneGraph::AgeColoredParticles(context, particles) {
    // Nop.
}
    
void AgeColoredParticles::Render() {
    int num = particles_->Count();
    if (num == 0)
        return;
    if (num > (int)vertexBuffer_.size() / 3) {
        vertexBuffer_.resize(num * 3);
        colorBuffer_.resize(num * 4);
        // See to it we have enough buffer space for all particles. The whole space might not be
        // needed, though, as particles can be hidden.
    }
    
    GLfloat *vertexPtr    = &vertexBuffer_[0],
            *colorPtr     = &colorBuffer_[0];
    int     numToRender   = 0,
            numColorSlots = (int)colors_.size() - 1;
    float   colorSlotSize = highAge_ / (float)numColorSlots;
    Vector<float> particleColor;
    for (Particles::ParticleInfo &particle : particles_->Iterate()) {
        if (particle.hidden)
            continue;
        int color = (int)(particle.age / highAge_ * (float)numColorSlots);
        NumberTools::Clamp(&color, 0, numColorSlots - 1);
        float t = (particle.age - (float)color*colorSlotSize) / colorSlotSize;
        NumberTools::Clamp(&t, 0.0f, 1.0f);
        particleColor = (1.0f - t)*colors_[color] + t*colors_[color + 1];
        *vertexPtr++ = particle.position.x;
        *vertexPtr++ = particle.position.y;
        *vertexPtr++ = particle.position.z;
        *colorPtr++  = particleColor.x;
        *colorPtr++  = particleColor.y;
        *colorPtr++  = particleColor.z;
        *colorPtr++  = 1.0f;
        numToRender++;
    }
    
    if (numToRender) {
        glPointSize(3.0f);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 0, &vertexBuffer_[0]);
        glColorPointer(4, GL_FLOAT, 0, &colorBuffer_[0]);
        glDrawArrays(GL_POINTS, 0, numToRender);
        glDisableClientState(GL_COLOR_ARRAY);
        glDisableClientState(GL_VERTEX_ARRAY);
    }
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
