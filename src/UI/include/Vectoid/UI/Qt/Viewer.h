#ifndef VECTOID_UI_QT_VIEWER_H_
#define VECTOID_UI_QT_VIEWER_H_

#include <memory>
#include <QOpenGLWidget>
#include <K/Core/Interface.h>
#include <Vectoid/Core/Transform.h>

namespace Vectoid {

namespace SceneGraph {
    class Camera;
    class PerspectiveProjection;
    class RenderTargetInterface;
    class Node;
    namespace OpenGL {
        class RenderTarget;
    }
}

//! UI elements for Vectoid 3D graphics.
namespace UI {
//! <c>Qt</c>-based UI elements for Vectoid 3D graphics.
namespace Qt {
//! <c>Qt</c>-based 3D viewer widget for displaying <c>Vectoid</c> scenes.
class Viewer : public QOpenGLWidget, public virtual K::Core::Interface {
    Q_OBJECT

  public:
    Viewer(QWidget *parent);
    //! Provides access to the viewer's render target.
    std::shared_ptr<Vectoid::SceneGraph::RenderTargetInterface> RenderTarget();
    //! Sets the scene graph to be viewed.
    void SetSceneGraph(const std::shared_ptr<Vectoid::SceneGraph::Node> &root,
                       const std::shared_ptr<Vectoid::SceneGraph::PerspectiveProjection> &projection,
                       const std::shared_ptr<Vectoid::SceneGraph::Camera> &camera);

  protected:
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

  private:
    std::shared_ptr<Vectoid::SceneGraph::OpenGL::RenderTarget>  renderTarget_;
    std::shared_ptr<Vectoid::SceneGraph::Node>                  root_;
    std::shared_ptr<Vectoid::SceneGraph::PerspectiveProjection> projection_;
    std::shared_ptr<Vectoid::SceneGraph::Camera>                camera_;
    int                                                         width_;
    int                                                         height_;
    int                                                         startX_;
    int                                                         startY_;
    Vectoid::Core::Vector<float>                                start_;
    Vectoid::Core::Transform<float>                             startCameraTransform_;
    Vectoid::Core::Vector<float>                                rotationCenter_;
    Vectoid::Core::Vector<float>                                virtualRotationCenter_;
    bool                                                        rotating_;
    bool                                                        panning_;
};

}    // Namespace Qt.
}    // Namespace UI.
}    // Namespace Vectoid.

#endif    // VECTOID_UI_QT_VIEWER_H_
