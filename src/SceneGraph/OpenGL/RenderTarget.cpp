///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/OpenGL/RenderTarget.h>

#include <Vectoid/SceneGraph/RenderVisitor.h>
#include <Vectoid/SceneGraph/OpenGL/AgeColoredParticles.h>
#include <Vectoid/SceneGraph/OpenGL/Camera.h>
#include <Vectoid/SceneGraph/OpenGL/ComboBarrel.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/CoordSys.h>
#include <Vectoid/SceneGraph/OpenGL/CustomPanel.h>
#include <Vectoid/SceneGraph/OpenGL/Geode.h>
#include <Vectoid/SceneGraph/OpenGL/Glyphs.h>
#include <Vectoid/SceneGraph/OpenGL/LineSegments.h>
#include <Vectoid/SceneGraph/OpenGL/LitColorCodedTriangles.h>
#include <Vectoid/SceneGraph/OpenGL/LitTriangles.h>
#include <Vectoid/SceneGraph/OpenGL/ParticlesRenderer.h>
#include <Vectoid/SceneGraph/OpenGL/PerspectiveProjection.h>
#include <Vectoid/SceneGraph/OpenGL/Points.h>
#include <Vectoid/SceneGraph/OpenGL/ScalarGrid2D.h>
#include <Vectoid/SceneGraph/OpenGL/SimpleGeometryRenderer.h>
#include <Vectoid/SceneGraph/OpenGL/SimpleLighting.h>
#include <Vectoid/SceneGraph/OpenGL/TerrainRenderer.h>
#include <Vectoid/SceneGraph/OpenGL/TestTriangle.h>
#include <Vectoid/SceneGraph/OpenGL/TextConsole.h>
#include <Vectoid/SceneGraph/OpenGL/TransparentTriangles.h>

using std::shared_ptr;
using std::make_shared;
using Vectoid::Core::LineSegmentProviderInterface;
using Vectoid::Core::Particles;
using Vectoid::Core::TriangleProviderInterface;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

RenderTarget::RenderTarget(const shared_ptr<Context> &context)
        : context_(context) {
    // Nop.
}

void RenderTarget::SetSceneGraph(const std::shared_ptr<TreeNode> &sceneGraphRoot) {
    sceneGraphRoot_ = sceneGraphRoot;
}

void RenderTarget::RenderFrame() {
    context_->ReleaseScheduledOpenGLResources();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (sceneGraphRoot_) {
        RenderVisitor renderVisitor;
        Visit(sceneGraphRoot_, &renderVisitor, false);
    }
}

shared_ptr<SceneGraph::AgeColoredParticles> RenderTarget::NewAgeColoredParticles(
        const shared_ptr<Particles> &particles) {
    return make_shared<AgeColoredParticles>(context_, particles);
}

shared_ptr<SceneGraph::Camera> RenderTarget::NewCamera() {
    return make_shared<Camera>(context_);
}

shared_ptr<SceneGraph::ComboBarrel> RenderTarget::NewComboBarrel(
        int width, int numVisibleOtherPerSide, float glyphWidth, float glyphHeight,
        const shared_ptr<SceneGraph::Glyphs> &glyphs) {
    return make_shared<ComboBarrel>(context_, width, numVisibleOtherPerSide, glyphWidth, glyphHeight, glyphs);
}

shared_ptr<SceneGraph::CoordSys> RenderTarget::NewCoordSys() {
    return make_shared<CoordSys>(context_);
}

shared_ptr<SceneGraph::CustomPanel> RenderTarget::NewCustomPanel(float width, float height) {
    return make_shared<CustomPanel>(context_, width, height);
}

shared_ptr<SceneGraph::Geode> RenderTarget::NewGeode(const std::shared_ptr<SceneGraph::Geometry> &geometry) {
    return make_shared<Geode>(context_, geometry);
}

shared_ptr<SceneGraph::Glyphs> RenderTarget::NewGlyphs() {
    return make_shared<Glyphs>(context_);
}

shared_ptr<SceneGraph::LineSegments> RenderTarget::NewLineSegments(
        const shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider) {
    return make_shared<LineSegments>(context_, lineSegmentProvider);
}

shared_ptr<SceneGraph::LitColorCodedTriangles> RenderTarget::NewLitColorCodedTriangles(
        const shared_ptr<TriangleProviderInterface> &triangleProvider) {
    return make_shared<LitColorCodedTriangles>(context_, triangleProvider);
}

shared_ptr<SceneGraph::LitTriangles> RenderTarget::NewLitTriangles(
        const shared_ptr<TriangleProviderInterface> &triangleProvider) {
    return make_shared<LitTriangles>(context_, triangleProvider);
}

shared_ptr<SceneGraph::ParticlesRenderer> RenderTarget::NewParticlesRenderer(
        const shared_ptr<Particles> &particles) {
    return make_shared<ParticlesRenderer>(context_, particles);
}

shared_ptr<SceneGraph::PerspectiveProjection> RenderTarget::NewPerspectiveProjection() {
    return make_shared<PerspectiveProjection>(context_);
}

shared_ptr<SceneGraph::Points> RenderTarget::NewPoints(const shared_ptr<DataSet::Points> &points) {
    return make_shared<Points>(context_, points);
}

shared_ptr<SceneGraph::ScalarGrid2D> RenderTarget::NewScalarGrid2D(
        float width, float height, int numColumns, int numRows) {
    return make_shared<ScalarGrid2D>(context_, width, height, numColumns, numRows);
}

shared_ptr<SceneGraph::SimpleGeometryRenderer> RenderTarget::NewSimpleGeometryRenderer(
        const shared_ptr<SceneGraph::SimpleGeometry> &geometry) {
    return make_shared<SimpleGeometryRenderer>(context_, geometry);
}

shared_ptr<SceneGraph::SimpleLighting> RenderTarget::NewSimpleLighting() {
    return make_shared<SimpleLighting>(context_);
}

shared_ptr<SceneGraph::TerrainRenderer> RenderTarget::NewTerrainRenderer(
        const shared_ptr<SceneGraph::Terrain> &terrain, const shared_ptr<SceneGraph::MapParameters> &mapParameters) {
    return make_shared<TerrainRenderer>(context_, terrain, mapParameters);
}

shared_ptr<SceneGraph::TestTriangle> RenderTarget::NewTestTriangle() {
    return make_shared<TestTriangle>(context_);
}

shared_ptr<SceneGraph::TextConsole> RenderTarget::NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const shared_ptr<SceneGraph::Glyphs> &glyphs) {
    return make_shared<TextConsole>(context_, width, height, glyphWidth, glyphHeight, glyphs);
}

shared_ptr<SceneGraph::TransparentTriangles> RenderTarget::NewTransparentTriangles(
        const shared_ptr<TriangleProviderInterface> &triangleProvider) {
    return make_shared<TransparentTriangles>(context_, triangleProvider);
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
