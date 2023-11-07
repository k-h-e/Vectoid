///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_RENDERTARGETINTERFACE_H_
#define VECTOID_SCENEGRAPH_RENDERTARGETINTERFACE_H_

#include <memory>
#include <K/Core/Interface.h>

namespace Vectoid {
    namespace Core {
        class LineSegmentProviderInterface;
        class Particles;
        class TriangleProviderInterface;
    }
    namespace DataSet {
        class Points;
    }
}
namespace Vectoid {
    namespace SceneGraph {
        class AgeColoredParticles;
        class Camera;
        class ComboBarrel;
        class CoordSys;
        class CustomPanel;
        class Geometry;
        class Geode;
        class Glyphs;
        class LitColorCodedTriangles;
        class LitTriangles;
        class LineSegments;
        struct MapParameters;
        class ParticlesRenderer;
        class PerspectiveProjection;
        class Points;
        class ScalarGrid2D;
        class SimpleGeometry;
        class SimpleGeometryRenderer;
        class SimpleLighting;
        class Terrain;
        class TerrainRenderer;
        class TestTriangle;
        class TextConsole;
        class TransparentTriangles;
        class TreeNode;
    }
}

namespace Vectoid {
namespace SceneGraph {

//! Interface to <c>Vectoid</c> render targets.
/*!
 *  A <c>Vectoid</c> render target acts as rendering-platform-specific factory for scene graph nodes and associated
 *  resources.
 */
class RenderTargetInterface : public virtual K::Core::Interface {
  public:
    virtual void SetSceneGraph(const std::shared_ptr<TreeNode> &sceneGraphRoot) = 0;
    //! Renders a frame using the current scene graph state.
    virtual void RenderFrame() = 0;
  
    virtual std::shared_ptr<AgeColoredParticles> NewAgeColoredParticles(
        const std::shared_ptr<Core::Particles> &particles) = 0;
    virtual std::shared_ptr<Camera> NewCamera() = 0;
    virtual std::shared_ptr<ComboBarrel> NewComboBarrel(
        int width, int numVisibleOtherPerSide, float glyphWidth, float glyphHeight,
        const std::shared_ptr<Glyphs> &glyphs) = 0;
    virtual std::shared_ptr<CoordSys> NewCoordSys() = 0;
    virtual std::shared_ptr<CustomPanel> NewCustomPanel(float width, float height) = 0;
    //! Can take <c>nullptr</c> as geometry.
    virtual std::shared_ptr<Geode> NewGeode(
        const std::shared_ptr<Geometry> &geometry) = 0;
    virtual std::shared_ptr<Glyphs> NewGlyphs() = 0;
    virtual std::shared_ptr<LineSegments> NewLineSegments(
        const std::shared_ptr<Core::LineSegmentProviderInterface> &lineSegmentProvider) = 0;
    virtual std::shared_ptr<LitColorCodedTriangles> NewLitColorCodedTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider) = 0;
    virtual std::shared_ptr<LitTriangles> NewLitTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider) = 0;
    virtual std::shared_ptr<ParticlesRenderer> NewParticlesRenderer(
        const std::shared_ptr<Core::Particles> &particles) = 0;
    virtual std::shared_ptr<PerspectiveProjection> NewPerspectiveProjection() = 0;
    virtual std::shared_ptr<Points> NewPoints(
        const std::shared_ptr<DataSet::Points> &points) = 0;
    virtual std::shared_ptr<ScalarGrid2D> NewScalarGrid2D(
        float width, float height, int numColumns, int numRows) = 0;
    virtual std::shared_ptr<SimpleGeometryRenderer> NewSimpleGeometryRenderer(
        const std::shared_ptr<SimpleGeometry> &geometry) = 0;
    virtual std::shared_ptr<SimpleLighting> NewSimpleLighting() = 0;
    virtual std::shared_ptr<TerrainRenderer> NewTerrainRenderer(
        const std::shared_ptr<Terrain> &terrain, const std::shared_ptr<MapParameters> &mapParameters) = 0;
    virtual std::shared_ptr<TestTriangle> NewTestTriangle() = 0;
    virtual std::shared_ptr<TextConsole> NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const std::shared_ptr<Glyphs> &glyphs) = 0;
    virtual std::shared_ptr<TransparentTriangles> NewTransparentTriangles(
        const std::shared_ptr<Core::TriangleProviderInterface> &triangleProvider) = 0;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_RENDERTARGETINTERFACE_H_

