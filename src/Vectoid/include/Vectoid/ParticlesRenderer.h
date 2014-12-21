//
//  ThrusterParticlesGeometry.h
//  kxm
//
//  Created by Kai Hergenroether on 5/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_VECTOID_PARTICLESRENDERER_H_
#define KXM_VECTOID_PARTICLESRENDERER_H_


#include <vector>
#include <memory>

#include <Vectoid/OpenGL.h>
#include <Vectoid/GeometryInterface.h>


namespace kxm {

namespace Vectoid {
    class RenderContext;
    class Particles;
}

namespace Zarch {

//! Renders particles.
/*!
 *  \ingroup Vectoid
 */
class ParticlesRenderer : public virtual Vectoid::GeometryInterface {
  public:
    ParticlesRenderer(std::shared_ptr<Vectoid::Particles> particles);
    
    void Render(Vectoid::RenderContext *context);
    
  private:
    ParticlesRenderer(const ParticlesRenderer &other);
    ParticlesRenderer &operator=(const ParticlesRenderer &other);
    
    std::shared_ptr<Vectoid::Particles> particles_;
    std::vector<GLfloat>                vertexBuffer_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_VECTOID_PARTICLESRENDERER_H_
