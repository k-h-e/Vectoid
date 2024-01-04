///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_VULKAN_SIMPLEGEOMETRYRENDERER_H_
#define VECTOID_SCENEGRAPH_VULKAN_SIMPLEGEOMETRYRENDERER_H_

#include <Vectoid/SceneGraph/SimpleGeometryRenderer.h>

#include <vector>
#include <Vectoid/SceneGraph/Vulkan/BufferInfo.h>

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

class Context;
class RenderTarget;

//! Renders simple geometry.
class SimpleGeometryRenderer : public SceneGraph::SimpleGeometryRenderer {
  public:
    friend class RenderTarget;
  
    SimpleGeometryRenderer(const SimpleGeometryRenderer &other) = delete;
    SimpleGeometryRenderer &operator=(const SimpleGeometryRenderer &other) = delete;
    ~SimpleGeometryRenderer();
    void Render();
    static void GetVertexInputInfo(VkVertexInputBindingDescription *binding,
                                   VkVertexInputAttributeDescription *attributes);
    
  private:
    SimpleGeometryRenderer(const std::shared_ptr<Vectoid::SceneGraph::Vulkan::Context> &context,
                           const std::shared_ptr<SimpleGeometry> &geometry);
    void createResources();
    void freeResources();
    
    std::shared_ptr<Vectoid::SceneGraph::Vulkan::Context> context_;
    Vectoid::SceneGraph::Vulkan::BufferInfo               vertexBuffer_;
    bool                                                  haveResources_;
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_SIMPLEGEOMETRYRENDERER_H_
