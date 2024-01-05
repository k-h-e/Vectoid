///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_VULKAN_RENDERTARGET_H_
#define VECTOID_SCENEGRAPH_VULKAN_RENDERTARGET_H_

#include <Vectoid/SceneGraph/RenderTargetInterface.h>

namespace Vectoid {
namespace SceneGraph {
//! <c>Vulkan</c> renderer (experimental, incomplete).
namespace Vulkan {

class Context;

//! <c>Vectoid</c> render target for rendering via <c>Vulkan</c>.
class RenderTarget : public virtual Vectoid::SceneGraph::RenderTargetInterface {
  public:
    RenderTarget(void *view);
    RenderTarget(const RenderTarget &other) = delete;
    RenderTarget &operator=(const RenderTarget &other) = delete;
    virtual void SetSceneGraph(const std::shared_ptr<Node> &sceneGraphRoot) override;
    virtual void RenderFrame() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::AgeColoredParticles> NewAgeColoredParticles(
        const std::shared_ptr<Vectoid::Core::Particles> &particles) override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::Camera> NewCamera() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::CoordSys> NewCoordSys() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::Geode> NewGeode(const std::shared_ptr<GeometryInterface> &geometry)
        override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::Glyphs> NewGlyphs() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::LineSegments> NewLineSegments(
        const std::shared_ptr<Core::LineSegmentProviderInterface> &lineSegmentProvider) override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::LitTriangles> NewLitTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider) override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::ParticlesRenderer> NewParticlesRenderer(
        const std::shared_ptr<Vectoid::Core::Particles> &particles) override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::PerspectiveProjection> NewPerspectiveProjection() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::SimpleGeometryRenderer> NewSimpleGeometryRenderer(
        const std::shared_ptr<::Vectoid::SceneGraph::SimpleGeometry> &geometry) override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::SimpleLighting> NewSimpleLighting() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::TerrainRenderer> NewTerrainRenderer(
        const std::shared_ptr<::Vectoid::SceneGraph::Terrain> &terrain,
        const std::shared_ptr<::Vectoid::SceneGraph::MapParameters> &mapParameters) override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::TestTriangle> NewTestTriangle() override;
    virtual std::shared_ptr<::Vectoid::SceneGraph::TextConsole> NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight,
        const std::shared_ptr<Vectoid::SceneGraph::Glyphs> &glyphs) override;
    
  protected:
    std::shared_ptr<Context>        context_;
    
  private:
    std::shared_ptr<Node> sceneGraphRoot_;
};

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_VULKAN_

