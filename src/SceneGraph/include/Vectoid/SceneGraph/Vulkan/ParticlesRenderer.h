///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_VULKAN_PARTICLESRENDERER_H_
#define VECTOID_SCENEGRAPH_VULKAN_PARTICLESRENDERER_H_

#include <vector>
#include <Vectoid/SceneGraph/ParticlesRenderer.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

class Context;
class RenderTarget;

//! Renders particles.
class ParticlesRenderer : public Vectoid::SceneGraph::ParticlesRenderer {
  public:
    ParticlesRenderer()                                          = delete;
    ParticlesRenderer(const ParticlesRenderer &other)            = delete;
    ParticlesRenderer &operator=(const ParticlesRenderer &other) = delete;
    ParticlesRenderer(ParticlesRenderer &&other)                 = delete;
    ParticlesRenderer &operator=(ParticlesRenderer &&other)      = delete;

    void Render();
    
  private:
    friend class RenderTarget;

    ParticlesRenderer(const std::shared_ptr<Context> &context,
                      const std::shared_ptr<Vectoid::Core::Particles> &particles);
    
    std::shared_ptr<Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.


#endif    // VECTOID_SCENEGRAPH_VULKAN_PARTICLESRENDERER_H_

