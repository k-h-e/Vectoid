///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/Vulkan/TerrainRenderer.h>

#include <K/Core/Log.h>
#include <K/Core/IntModN.h>
#include <Vectoid/SceneGraph/Terrain.h>
#include <Vectoid/SceneGraph/MapParameters.h>

using namespace std;
using K::Core::Log;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

TerrainRenderer::TerrainRenderer(const shared_ptr<Vectoid::SceneGraph::Vulkan::Context> &context,
                                 const shared_ptr<Terrain> &terrain, const shared_ptr<MapParameters> &mapParameters)
        : SceneGraph::TerrainRenderer(terrain, mapParameters),
          context_(context) {

}

void TerrainRenderer::Render() {
    Log::Print(Log::Level::Debug, nullptr, []{ return "Vulkan::TerrainRenderer::Render()"; });
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

