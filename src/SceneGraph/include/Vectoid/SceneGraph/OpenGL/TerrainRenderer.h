///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_TERRAINRENDERER_H_
#define VECTOID_SCENEGRAPH_OPENGL_TERRAINRENDERER_H_

#include <Vectoid/SceneGraph/TerrainRenderer.h>

#include <Vectoid/SceneGraph/OpenGL/OpenGL.h>

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

class Context;
class RenderTarget;

//! Renders the terrain.
class TerrainRenderer : public SceneGraph::TerrainRenderer {
  public:
    TerrainRenderer()                                        = delete;
    TerrainRenderer(const std::shared_ptr<Context> &context, const std::shared_ptr<Terrain> &terrain,
                    const std::shared_ptr<MapParameters> &mapParameters);
    TerrainRenderer(const TerrainRenderer &other)            = delete;
    TerrainRenderer &operator=(const TerrainRenderer &other) = delete;
    TerrainRenderer(TerrainRenderer &&other)                 = delete;
    TerrainRenderer &operator=(TerrainRenderer &&other)      = delete;

    void Render() override;
    
  private:
    std::vector<GLfloat> vertices_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_TERRAINRENDERER_H_
