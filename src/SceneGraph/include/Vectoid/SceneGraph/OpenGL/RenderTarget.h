///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_OPENGL_RENDERTARGET_H_
#define VECTOID_SCENEGRAPH_OPENGL_RENDERTARGET_H_

#include <Vectoid/SceneGraph/RenderTargetInterface.h>

namespace Vectoid {
    namespace SceneGraph {
        namespace OpenGL {
            class Context;
        }
    }
}

namespace Vectoid {
namespace SceneGraph {
//! <c>OpenGL</c> renderer.
namespace OpenGL {

//! <c>Vectoid</c> render target for rendering via <c>OpenGL</c>.
class RenderTarget : public virtual Vectoid::SceneGraph::RenderTargetInterface {
  public:
    RenderTarget()                                     = delete;
    RenderTarget(const std::shared_ptr<Context> &context);
    RenderTarget(const RenderTarget &other)            = delete;
    RenderTarget &operator=(const RenderTarget &other) = delete;
    RenderTarget(RenderTarget &&other)                 = delete;
    RenderTarget &operator=(RenderTarget &&other)      = delete;

    void SetSceneGraph(const std::shared_ptr<TreeNode> &sceneGraphRoot) override;
    void RenderFrame() override;
    std::shared_ptr<SceneGraph::AgeColoredParticles> NewAgeColoredParticles(
        const std::shared_ptr<Core::Particles> &particles) override;
    std::shared_ptr<SceneGraph::Camera> NewCamera() override;
    std::shared_ptr<SceneGraph::ComboBarrel> NewComboBarrel(
        int width, int numVisibleOtherPerSide, float glyphWidth, float glyphHeight,
        const std::shared_ptr<SceneGraph::Glyphs> &glyphs) override;
    std::shared_ptr<SceneGraph::CoordSys> NewCoordSys() override;
    std::shared_ptr<SceneGraph::CustomPanel> NewCustomPanel(float width, float height) override;
    std::shared_ptr<SceneGraph::Geode> NewGeode(const std::shared_ptr<SceneGraph::Geometry> &geometry) override;
    std::shared_ptr<SceneGraph::Glyphs> NewGlyphs() override;
    std::shared_ptr<SceneGraph::LineSegments> NewLineSegments(
        const std::shared_ptr<Core::LineSegmentProviderInterface> &lineSegmentProvider) override;
    std::shared_ptr<SceneGraph::LitColorCodedTriangles> NewLitColorCodedTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider) override;
    std::shared_ptr<SceneGraph::LitTriangles> NewLitTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider) override;
    std::shared_ptr<SceneGraph::ParticlesRenderer> NewParticlesRenderer(
        const std::shared_ptr<Core::Particles> &particles) override;
    std::shared_ptr<SceneGraph::PerspectiveProjection> NewPerspectiveProjection() override;
    std::shared_ptr<SceneGraph::Points> NewPoints(
        const std::shared_ptr<DataSet::Points> &points) override;
    std::shared_ptr<SceneGraph::ScalarGrid2D> NewScalarGrid2D(
        float width, float height, int numColumns, int numRows) override;
    std::shared_ptr<SceneGraph::SimpleGeometryRenderer> NewSimpleGeometryRenderer(
        const std::shared_ptr<SceneGraph::SimpleGeometry> &geometry) override;
    std::shared_ptr<SceneGraph::SimpleLighting> NewSimpleLighting() override;
    std::shared_ptr<SceneGraph::TerrainRenderer> NewTerrainRenderer(
        const std::shared_ptr<SceneGraph::Terrain> &terrain,
        const std::shared_ptr<SceneGraph::MapParameters> &mapParameters) override;
    std::shared_ptr<SceneGraph::TestTriangle> NewTestTriangle() override;
    std::shared_ptr<SceneGraph::TextConsole> NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const std::shared_ptr<SceneGraph::Glyphs> &glyphs)
        override;
    std::shared_ptr<SceneGraph::TransparentTriangles> NewTransparentTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider) override;
    
  private:
    std::shared_ptr<Context>  context_;
    std::shared_ptr<TreeNode> sceneGraphRoot_;
};

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_OPENGL_RENDERTARGET_H_
