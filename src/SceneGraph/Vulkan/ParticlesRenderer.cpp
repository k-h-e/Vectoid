///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/ParticlesRenderer.h>

#include <K/Core/Log.h>
#include <Vectoid/Core/Particles.h>

using namespace std;
using K::Core::Log;
using Vectoid::Core::Particles;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

ParticlesRenderer::ParticlesRenderer(const shared_ptr<Context> &context, const shared_ptr<Particles> &particles)
        : Vectoid::SceneGraph::ParticlesRenderer(particles),
          context_(context) {
    // Nop.
}

void ParticlesRenderer::Render() {
    Log::Print(Log::Level::Debug, this, []{ return "Vulkan::ParticlesRenderer::Render()"; });
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
