//
//  ThrusterParticlesGeometry.h
//  kxm
//
//  Created by Kai Hergenroether on 5/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_THRUSTERPARTICLESGEOMETRY_H_
#define KXM_ZARCH_THRUSTERPARTICLESGEOMETRY_H_


#include <vector>

#include <boost/shared_ptr.hpp>

#include <kxm/Vectoid/OpenGL.h>
#include <kxm/Vectoid/GeometryInterface.h>


namespace kxm {

namespace Vectoid {
    class RenderContext;
    class Particles;
}

namespace Zarch {

//! Renders the lander's thruster particles.
/*!
 *  \ingroup Zarch
 */
class ThrusterParticlesGeometry : public virtual Vectoid::GeometryInterface {
  public:
    ThrusterParticlesGeometry(boost::shared_ptr<Vectoid::Particles> particles);
    
    void Render(Vectoid::RenderContext *context);
    
  private:
    ThrusterParticlesGeometry(const ThrusterParticlesGeometry &other);
    ThrusterParticlesGeometry &operator=(const ThrusterParticlesGeometry &other);
    
    boost::shared_ptr<Vectoid::Particles> particles_;
    std::vector<GLfloat>                  vertexBuffer_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_THRUSTERPARTICLESGEOMETRY_H_
