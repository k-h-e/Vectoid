///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_PARTICLESRENDERER_H_
#define VECTOID_SCENEGRAPH_PARTICLESRENDERER_H_

#include <vector>
#include <memory>
#include <Vectoid/SceneGraph/Geometry.h>

namespace Vectoid {
namespace Core {
    class Particles;
}
}

namespace Vectoid {
namespace SceneGraph {

//! Renders particles.
class ParticlesRenderer : public Geometry {
  public:
    ParticlesRenderer()                                          = delete;
    ParticlesRenderer(const ParticlesRenderer &other)            = delete;
    ParticlesRenderer &operator=(const ParticlesRenderer &other) = delete;
    ParticlesRenderer(ParticlesRenderer &&other)                 = delete;
    ParticlesRenderer &operator=(ParticlesRenderer &&other)      = delete;
    
  protected:
    ParticlesRenderer(const std::shared_ptr<Context> &context, const std::shared_ptr<Core::Particles> &particles);
  
    std::shared_ptr<Core::Particles> particles_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_PARTICLESRENDERER_H_
