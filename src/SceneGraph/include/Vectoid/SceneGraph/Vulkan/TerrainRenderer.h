///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_VULKAN_TERRAINRENDERER_H_
#define VECTOID_SCENEGRAPH_VULKAN_TERRAINRENDERER_H_

#include <memory>
#include <Vectoid/SceneGraph/TerrainRenderer.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

class Context;
class RenderTarget;

//! Renders the terrain.
class TerrainRenderer : public SceneGraph::TerrainRenderer {
  public:
    TerrainRenderer()                                        = delete;
    TerrainRenderer(const TerrainRenderer &other)            = delete;
    TerrainRenderer &operator=(const TerrainRenderer &other) = delete;
    TerrainRenderer(TerrainRenderer &&other)                 = delete;
    TerrainRenderer &operator=(TerrainRenderer &&other)      = delete;

    void Render() override ;
    
  private:
    friend class RenderTarget;

    TerrainRenderer(const std::shared_ptr<Vectoid::SceneGraph::Vulkan::Context> &context,
                    const std::shared_ptr<Terrain> &terrain, const std::shared_ptr<MapParameters> &mapParameters);
  
    std::shared_ptr<Vectoid::SceneGraph::Vulkan::Context> context_;
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_TERRAINRENDERER_H_

