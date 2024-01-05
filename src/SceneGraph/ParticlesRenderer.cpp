///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/ParticlesRenderer.h>

using namespace std;
using Vectoid::Core::Particles;


namespace Vectoid {
namespace SceneGraph {

ParticlesRenderer::ParticlesRenderer(const shared_ptr<Context> &context, const shared_ptr<Particles> &particles)
        : Geometry(context),
          particles_(particles) {
    // Nop.
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
