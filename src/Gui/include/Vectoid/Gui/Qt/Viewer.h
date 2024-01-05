///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_GUI_QT_VIEWER_H_
#define VECTOID_GUI_QT_VIEWER_H_

#include <memory>
#include <QOpenGLWidget>
#include <K/Core/Interface.h>
#include <Vectoid/Core/Transform.h>

namespace Vectoid {

namespace SceneGraph {
    class Camera;
    class PerspectiveProjection;
    class RenderTargetInterface;
    class TreeNode;
    namespace OpenGL {
        class Context;
        class RenderTarget;
    }
}

//! UI elements for Vectoid 3D graphics.
namespace Gui {
//! <c>Qt</c>-based UI elements for Vectoid 3D graphics.
namespace Qt {
//! <c>Qt</c>-based 3D viewer widget for displaying <c>Vectoid</c> scenes.
class Viewer : public QOpenGLWidget, public virtual K::Core::Interface {
    Q_OBJECT

  public:
    Viewer(QWidget *parent);
    Viewer(const Viewer &other)            = delete;
    Viewer &operator=(const Viewer &other) = delete;
    Viewer(Viewer &&other)                 = delete;
    Viewer &operator=(Viewer &&other)      = delete;
    ~Viewer();

    //! Provides access to the viewer's render target.
    std::shared_ptr<Vectoid::SceneGraph::RenderTargetInterface> RenderTarget();
    //! Sets the scene graph to be viewed.
    void SetSceneGraph(const std::shared_ptr<Vectoid::SceneGraph::TreeNode> &root,
                       const std::shared_ptr<Vectoid::SceneGraph::PerspectiveProjection> &projection,
                       const std::shared_ptr<Vectoid::SceneGraph::Camera> &camera);
    //! Toggles interactive camera navigation.
    /*!
     *  When camera navigation is disabled, mouse dragging is reported via the respective signals.
     */
    void EnableCameraNavigation(bool enabled);

  signals:
    //! Emitted when the projection has been updated by the viewer.
    void ProjectionUpdated();
    //! Emitted when the camera has been updated by the viewer.
    void CameraUpdated();
    //! Reports mouse drags in case camera navigation is turned off.
    void MouseDragStateChanged(bool dragging);
    //! Reports mouse drags in case camera navigation is turned off.
    /*!
     *  Drags are reported in multiples of the window size, and with respect to the dragging start point.
     */
    void MouseDragged(float x, float y);
    //! Reports mouse moves.
    void MouseMoved(Vectoid::Core::Vector<float> cameraSpacePosition);
    //! Reports that the mouse has been clicked.
    void MouseClicked();

  protected:
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

  private slots:
    void OnGLContextAboutToBeDestroyed();

  private:
    QOpenGLContext                                              *qtGLContext_;
    std::shared_ptr<Vectoid::SceneGraph::OpenGL::Context>       context_;
    std::shared_ptr<Vectoid::SceneGraph::OpenGL::RenderTarget>  renderTarget_;
    std::shared_ptr<Vectoid::SceneGraph::TreeNode>              root_;
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
    bool                                                        movingRolling_;
    bool                                                        dragging_;
    bool                                                        mouseMovedWhilePressed_;
    bool                                                        cameraNavigationEnabled_;
    bool                                                        altKeyDown_;
    bool                                                        controlKeyDown_;
};

}    // Namespace Qt.
}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_QT_VIEWER_H_
