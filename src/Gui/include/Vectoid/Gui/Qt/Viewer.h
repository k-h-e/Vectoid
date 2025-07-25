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
#include <K/Core/StopWatch.h>
#include <Vectoid/Core/Transform.h>
#include <Vectoid/Gui/TouchInfo.h>

namespace Vectoid {
    namespace Core {
        template<typename T> class Vector;
    }
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
    namespace Gui {
        class Gui;
    }
}

namespace Vectoid {
//! UI elements for Vectoid 3D graphics.
namespace Gui {
//! <c>Qt</c>-based UI elements for Vectoid 3D graphics.
namespace Qt {
//! <c>Qt</c>-based 3D viewer widget for displaying <c>Vectoid</c> scenes.
class Viewer : public QOpenGLWidget, public virtual K::Core::Interface {
    Q_OBJECT

  public:
    Viewer(QWidget *parent, const Core::Vector<float> &backgroundColor);
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
    //! Sets the specified GUI.
    void SetGui(const std::shared_ptr<Vectoid::Gui::Gui> &gui, float guiDeltaZ);
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
    void OnTimer();
    void OnGLContextAboutToBeDestroyed();

  private:
    void SetViewPort();
    void UpdateKeyNavigation();

    QOpenGLContext                                              *qtGLContext_;
    QTimer                                                      *timer_;
    std::shared_ptr<Vectoid::SceneGraph::OpenGL::Context>       context_;
    std::shared_ptr<Vectoid::SceneGraph::OpenGL::RenderTarget>  renderTarget_;
    std::shared_ptr<Vectoid::SceneGraph::PerspectiveProjection> projection_;
    std::shared_ptr<Vectoid::SceneGraph::Camera>                camera_;
    int                                                         width_;
    int                                                         height_;
    std::shared_ptr<Vectoid::Gui::Gui>                          gui_;
    float                                                       guiDeltaZ_;
    int                                                         startX_;
    int                                                         startY_;
    Vectoid::Core::Vector<float>                                start_;
    Vectoid::Core::Transform<float>                             startCameraTransform_;
    Vectoid::Core::Vector<float>                                rotationCenter_;
    Vectoid::Core::Vector<float>                                virtualRotationCenter_;
    bool                                                        moveForwardKeyDown_;
    bool                                                        moveBackwardKeyDown_;
    bool                                                        strafeLeftKeyDown_;
    bool                                                        strafeRightKeyDown_;
    bool                                                        strafeUpKeyDown_;
    bool                                                        strafeDownKeyDown_;
    bool                                                        rotateLeftKeyDown_;
    bool                                                        rotateRightKeyDown_;
    bool                                                        rotateUpKeyDown_;
    bool                                                        rotateDownKeyDown_;
    bool                                                        rollLeftKeyDown_;
    bool                                                        rollRightKeyDown_;
    bool                                                        slowKeyDown_;
    std::optional<float>                                        currentMoveSpeedMPerS_;
    std::optional<float>                                        currentStrafeSpeedLeftRightMPerS_;
    std::optional<float>                                        currentStrafeSpeedUpDownMPerS_;
    std::optional<float>                                        currentRotateSpeedLeftRightDegreesPerS_;
    std::optional<float>                                        currentRotateSpeedUpDownDegreesPerS_;
    std::optional<float>                                        currentRollSpeedDegreesPerS_;
    bool                                                        rotating_;
    bool                                                        dragging_;
    bool                                                        mouseMovedWhilePressed_;
    bool                                                        cameraNavigationEnabled_;
    Vectoid::Gui::TouchInfo                                     touchInfo_;
    std::vector<const Vectoid::Gui::TouchInfo *>                touches_;
    bool                                                        guiIsHandlingMouse_;
    K::Core::StopWatch                                          timerStopWatch_;
    float                                                       moveSpeedMPerS_;
    float                                                       rotateSpeedDegreesPerS_;
    float                                                       moveSlowFactor_;
    float                                                       rotateSlowFactor_;
};

}    // Namespace Qt.
}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_QT_VIEWER_H_
