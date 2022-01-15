#include <Vectoid/SceneGraph/OpenGL/RenderTarget.h>

#include <Vectoid/SceneGraph/RenderVisitor.h>
#include <Vectoid/SceneGraph/OpenGL/AgeColoredParticles.h>
#include <Vectoid/SceneGraph/OpenGL/Camera.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/CoordSys.h>
#include <Vectoid/SceneGraph/OpenGL/Geode.h>
#include <Vectoid/SceneGraph/OpenGL/Glyphs.h>
#include <Vectoid/SceneGraph/OpenGL/LineSegments.h>
#include <Vectoid/SceneGraph/OpenGL/LitColorCodedTriangles.h>
#include <Vectoid/SceneGraph/OpenGL/LitTriangles.h>
#include <Vectoid/SceneGraph/OpenGL/ParticlesRenderer.h>
#include <Vectoid/SceneGraph/OpenGL/PerspectiveProjection.h>
#include <Vectoid/SceneGraph/OpenGL/Points.h>
#include <Vectoid/SceneGraph/OpenGL/SimpleGeometryRenderer.h>
#include <Vectoid/SceneGraph/OpenGL/SimpleLighting.h>
#include <Vectoid/SceneGraph/OpenGL/TerrainRenderer.h>
#include <Vectoid/SceneGraph/OpenGL/TestTriangle.h>
#include <Vectoid/SceneGraph/OpenGL/TextConsole.h>

using std::shared_ptr;
using std::make_shared;
using Vectoid::Core::LineSegmentProviderInterface;
using Vectoid::Core::Particles;
using Vectoid::Core::TriangleProviderInterface;

namespace Vectoid {
namespace SceneGraph {
namespace OpenGL {

RenderTarget::RenderTarget()
        : glInitialized_(false) {
    context_ = make_shared<Context>();
}

void RenderTarget::SetSceneGraph(const std::shared_ptr<TreeNode> &sceneGraphRoot) {
    sceneGraphRoot_ = sceneGraphRoot;
}

void RenderTarget::RenderFrame() {
    if (!glInitialized_) {
        initializeGL();
        glInitialized_ = true;
    }

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if (sceneGraphRoot_) {
        RenderVisitor renderVisitor;
        Visit(sceneGraphRoot_, &renderVisitor, false);
    }
}

shared_ptr<::Vectoid::SceneGraph::AgeColoredParticles> RenderTarget::NewAgeColoredParticles(
        const shared_ptr<Particles> &particles) {
    return shared_ptr<OpenGL::AgeColoredParticles>(new AgeColoredParticles(context_, particles));
}

shared_ptr<::Vectoid::SceneGraph::Camera> RenderTarget::NewCamera() {
    return shared_ptr<OpenGL::Camera>(new Camera(context_));
}

shared_ptr<::Vectoid::SceneGraph::CoordSys> RenderTarget::NewCoordSys() {
    return shared_ptr<OpenGL::CoordSys>(new CoordSys(context_));
}

shared_ptr<::Vectoid::SceneGraph::Geode> RenderTarget::NewGeode(const std::shared_ptr<Geometry> &geometry) {
    return shared_ptr<OpenGL::Geode>(new Geode(context_, geometry));
}

shared_ptr<::Vectoid::SceneGraph::Glyphs> RenderTarget::NewGlyphs() {
    return shared_ptr<OpenGL::Glyphs>(new Glyphs(context_));
}

shared_ptr<::Vectoid::SceneGraph::LineSegments> RenderTarget::NewLineSegments(
        const shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider) {
    return make_shared<OpenGL::LineSegments>(context_, lineSegmentProvider);
}

shared_ptr<::Vectoid::SceneGraph::LitColorCodedTriangles> RenderTarget::NewLitColorCodedTriangles(
        const shared_ptr<TriangleProviderInterface> &triangleProvider) {
    return make_shared<OpenGL::LitColorCodedTriangles>(context_, triangleProvider);
}

shared_ptr<::Vectoid::SceneGraph::LitTriangles> RenderTarget::NewLitTriangles(
        const shared_ptr<TriangleProviderInterface> &triangleProvider) {
    return make_shared<OpenGL::LitTriangles>(context_, triangleProvider);
}

shared_ptr<::Vectoid::SceneGraph::ParticlesRenderer> RenderTarget::NewParticlesRenderer(
        const shared_ptr<Particles> &particles) {
    return shared_ptr<OpenGL::ParticlesRenderer>(new ParticlesRenderer(context_, particles));
}

shared_ptr<::Vectoid::SceneGraph::PerspectiveProjection> RenderTarget::NewPerspectiveProjection() {
    return shared_ptr<OpenGL::PerspectiveProjection>(new PerspectiveProjection(context_));
}

shared_ptr<::Vectoid::SceneGraph::Points> RenderTarget::NewPoints(const shared_ptr<DataSet::Points> &points) {
    return make_shared<OpenGL::Points>(context_, points);
}

shared_ptr<::Vectoid::SceneGraph::SimpleGeometryRenderer> RenderTarget::NewSimpleGeometryRenderer(
        const shared_ptr<::Vectoid::SceneGraph::SimpleGeometry> &geometry) {
    return shared_ptr<OpenGL::SimpleGeometryRenderer>(new SimpleGeometryRenderer(context_, geometry));
}

shared_ptr<::Vectoid::SceneGraph::SimpleLighting> RenderTarget::NewSimpleLighting() {
    return make_shared<OpenGL::SimpleLighting>(context_);
}

shared_ptr<::Vectoid::SceneGraph::TerrainRenderer> RenderTarget::NewTerrainRenderer(
        const shared_ptr<::Vectoid::SceneGraph::Terrain> &terrain,
        const shared_ptr<::Vectoid::SceneGraph::MapParameters> &mapParameters) {
    return shared_ptr<OpenGL::TerrainRenderer>(new TerrainRenderer(context_, terrain, mapParameters));
}

shared_ptr<::Vectoid::SceneGraph::TestTriangle> RenderTarget::NewTestTriangle() {
    return shared_ptr<OpenGL::TestTriangle>(new TestTriangle(context_));
}

shared_ptr<::Vectoid::SceneGraph::TextConsole> RenderTarget::NewTextConsole(
        int width, int height, float glyphWidth, float glyphHeight, const shared_ptr<SceneGraph::Glyphs> &glyphs) {
    return shared_ptr<OpenGL::TextConsole>(new TextConsole(context_, width, height, glyphWidth, glyphHeight, glyphs));
}

void RenderTarget::initializeGL() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_LIGHT0);
}

}    // Namespace OpenGL.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
