///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Gui/Qt/Viewer.h>

#include <QMouseEvent>
#include <QOpenGLContext>
#include <QTimer>
#include <QWheelEvent>

#include <K/Core/NumberTools.h>
#include <K/Core/Log.h>
#include <Vectoid/SceneGraph/Camera.h>
#include <Vectoid/SceneGraph/Context.h>
#include <Vectoid/SceneGraph/PerspectiveProjection.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/RenderTarget.h>
#include <Vectoid/Gui/Gui.h>

using std::make_shared;
using std::nullopt;
using std::shared_ptr;
using std::to_string;
using K::Core::NumberTools;
using K::Core::Log;
using Vectoid::Core::Axis;
using Vectoid::Core::Vector;
using Vectoid::Core::Transform;
using Vectoid::SceneGraph::Camera;
using Vectoid::SceneGraph::PerspectiveProjection;
using Vectoid::SceneGraph::RenderTargetInterface;
using Vectoid::SceneGraph::TreeNode;
using Vectoid::SceneGraph::OpenGL::Context;
using Vectoid::SceneGraph::OpenGL::RenderTarget;
using Vectoid::Gui::Position;
using Vectoid::Gui::Size;

namespace Vectoid {
namespace Gui {
namespace Qt {

Viewer::Viewer(QWidget *parent)
        : QOpenGLWidget{parent},
          qtGLContext_{nullptr},
          width_{1},
          height_{1},
          guiDeltaZ_{0.0f},
          moveForwardKeyDown_{false},
          moveBackwardKeyDown_{false},
          strafeLeftKeyDown_{false},
          strafeRightKeyDown_{false},
          strafeUpKeyDown_{false},
          strafeDownKeyDown_{false},
          rotateLeftKeyDown_{false},
          rotateRightKeyDown_{false},
          rotateUpKeyDown_{false},
          rotateDownKeyDown_{false},
          rollLeftKeyDown_{false},
          rollRightKeyDown_{false},
          slowKeyDown_{false},
          rotating_{false},
          dragging_{false},
          mouseMovedWhilePressed_{false},
          cameraNavigationEnabled_{true},
          guiIsHandlingMouse_{false},
          moveSpeedMPerS_{120.0f},
          rotateSpeedDegreesPerS_{180.0f},
          slowFactor_{.1f} {
    setMouseTracking(true);
    setFocusPolicy(::Qt::ClickFocus);

    timer_ = new QTimer{this};
    timer_->setInterval(0);
    QObject::connect(timer_, &QTimer::timeout, this, &Viewer::OnTimer);
    
    context_      = make_shared<SceneGraph::OpenGL::Context>();
    renderTarget_ = make_shared<class RenderTarget>(context_);

    touches_.push_back(&touchInfo_);
}

Viewer::~Viewer() {
    if (qtGLContext_) {
        makeCurrent();
        context_->ReleaseOpenGLResources();

        disconnect(qtGLContext_, &QOpenGLContext::aboutToBeDestroyed, this, &Viewer::OnGLContextAboutToBeDestroyed);
        qtGLContext_ = nullptr;
    }
}

shared_ptr<RenderTargetInterface> Viewer::RenderTarget() {
    return renderTarget_;
}

void Viewer::SetSceneGraph(const shared_ptr<TreeNode> &root, const shared_ptr<PerspectiveProjection> &projection,
                           const shared_ptr<Camera> &camera) {
    projection_ = projection;
    camera_     = camera;

    renderTarget_->SetSceneGraph(root);

    SetViewPort();
}

void Viewer::SetGui(const shared_ptr<Gui> &gui, float guiDeltaZ) {
    gui_       = gui;
    guiDeltaZ_ = guiDeltaZ;
    NumberTools::ClampMin(&guiDeltaZ_, 0.0f);

    SetViewPort();
}

void Viewer::EnableCameraNavigation(bool enabled) {
    cameraNavigationEnabled_ = enabled;
    rotating_ = false;
    dragging_ = false;

    UpdateKeyNavigation();
}

void Viewer::initializeGL() {
    qtGLContext_ = context();
    assert(qtGLContext_);
    connect(qtGLContext_, &QOpenGLContext::aboutToBeDestroyed, this, &Viewer::OnGLContextAboutToBeDestroyed);
    context_->InitializeGL();
}

void Viewer::paintGL() {
    if (gui_) {
        gui_->OnFrameWillBeRendered();
    }
    renderTarget_->RenderFrame();
}

void Viewer::resizeGL(int width, int height) {
    NumberTools::ClampMin(&width, 1);
    NumberTools::ClampMin(&height, 1);
    width_  = width;
    height_ = height;
    SetViewPort();
}

void Viewer::mousePressEvent(QMouseEvent *event) {
    guiIsHandlingMouse_ = false;

    if (projection_ && gui_) {
        auto point = projection_->TransformViewPortCoordinates(static_cast<float>(event->pos().x()),
                                                               static_cast<float>(event->pos().y()), -guiDeltaZ_);
        touchInfo_ = TouchInfo{point.x, point.y};

        guiIsHandlingMouse_ = gui_->OnTouchGestureBegan(touches_);
    }

    if (!guiIsHandlingMouse_) {
        rotating_      = false;
        dragging_      = false;

        if (cameraNavigationEnabled_) {
            if (camera_) {
                camera_->GetTransform(&startCameraTransform_);
                rotating_ = true;
            }
        } else {
            dragging_ = true;
        }

        if (rotating_ || dragging_) {
            startX_                 = event->pos().x();
            startY_                 = event->pos().y();
            mouseMovedWhilePressed_ = false;
            UpdateKeyNavigation();

            if (dragging_) {
                emit MouseDragStateChanged(true);
            }
        }
    }
}

void Viewer::mouseReleaseEvent(QMouseEvent *event) {
    if (guiIsHandlingMouse_) {
        if (projection_ && gui_) {
            auto point = projection_->TransformViewPortCoordinates(static_cast<float>(event->pos().x()),
                                                                   static_cast<float>(event->pos().y()), -guiDeltaZ_);
            touchInfo_.x = point.x;
            touchInfo_.y = point.y;
            gui_->OnTouchGestureEnded(touches_);
        }
        guiIsHandlingMouse_ = false;
    } else {
        bool didDrag = dragging_;

        rotating_  = false;
        dragging_  = false;
        UpdateKeyNavigation();

        if (didDrag) {
            emit MouseDragStateChanged(false);
        }
        if (!mouseMovedWhilePressed_) {
            emit MouseClicked();
        }
    }
}

void Viewer::mouseMoveEvent(QMouseEvent *event) {
    if (guiIsHandlingMouse_) {
        if (projection_ && gui_) {
            auto point = projection_->TransformViewPortCoordinates(static_cast<float>(event->pos().x()),
                                                                   static_cast<float>(event->pos().y()), -guiDeltaZ_);
            touchInfo_.x = point.x;
            touchInfo_.y = point.y;
            gui_->OnTouchGestureMoved(touches_);
        }
    } else {
        if (!mouseMovedWhilePressed_) {
            if ((event->pos().x() != startX_) || (event->pos().y() != startY_)) {
                mouseMovedWhilePressed_ = true;
            }
        }

        if (projection_) {
            Vector<float> current = projection_->TransformViewPortCoordinates(static_cast<float>(event->pos().x()),
                                                                              static_cast<float>(event->pos().y()));
            Vector<float> start   = projection_->TransformViewPortCoordinates(static_cast<float>(startX_),
                                                                              static_cast<float>(startY_));
            if (rotating_) {
                if (camera_) {
                    float yawAngle   =  (current.x - start.x)/projection_->WindowSize() * 90.0f;
                    float pitchAngle = -(current.y - start.y)/projection_->WindowSize() * 90.0f;
                    Transform<float> transform = startCameraTransform_;
                    transform.Prepend(Transform(Axis::Y, yawAngle));
                    transform.Prepend(Transform(Axis::X, pitchAngle));
                    camera_->SetTransform(transform);
                    update();
                    emit CameraUpdated();
                }
            } else if (dragging_) {
                emit MouseDragged((current.x - start.x)/projection_->WindowSize(),
                                  (current.y - start.y)/projection_->WindowSize());
            }

            emit MouseMoved(current);
        }
    }
}

void Viewer::keyPressEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        switch (event->key()) {
            case ::Qt::Key_W:
                moveForwardKeyDown_  = true;
                break;
            case ::Qt::Key_S:
                moveBackwardKeyDown_ = true;
                break;
            case ::Qt::Key_A:
                strafeLeftKeyDown_   = true;
                break;
            case ::Qt::Key_D:
                strafeRightKeyDown_  = true;
                break;
            case ::Qt::Key_R:
                strafeUpKeyDown_     = true;
                break;
            case ::Qt::Key_F:
                strafeDownKeyDown_   = true;
                break;
            case ::Qt::Key_Left:
                rotateLeftKeyDown_   = true;
                break;
            case ::Qt::Key_Right:
                rotateRightKeyDown_  = true;
                break;
            case ::Qt::Key_Up:
                rotateDownKeyDown_   = true;      // Inversion.
                break;
            case ::Qt::Key_Down:
                rotateUpKeyDown_     = true;        // Inversion.
                break;
            case ::Qt::Key_Q:
                rollLeftKeyDown_     = true;
                break;
            case ::Qt::Key_E:
                rollRightKeyDown_    = true;
                break;
            case ::Qt::Key_Shift:
                slowKeyDown_         = true;
                break;
            default:
                QOpenGLWidget::keyPressEvent(event);
                break;
        }

        UpdateKeyNavigation();
        
    } else {
        QOpenGLWidget::keyPressEvent(event);
    }
}

void Viewer::keyReleaseEvent(QKeyEvent *event) {
    if (!event->isAutoRepeat()) {
        switch (event->key()) {
            case ::Qt::Key_W:
                moveForwardKeyDown_  = false;
                break;
            case ::Qt::Key_S:
                moveBackwardKeyDown_ = false;
                break;
            case ::Qt::Key_A:
                strafeLeftKeyDown_   = false;
                break;
            case ::Qt::Key_D:
                strafeRightKeyDown_  = false;
                break;
            case ::Qt::Key_R:
                strafeUpKeyDown_     = false;
                break;
            case ::Qt::Key_F:
                strafeDownKeyDown_   = false;
                break;
            case ::Qt::Key_Left:
                rotateLeftKeyDown_   = false;
                break;
            case ::Qt::Key_Right:
                rotateRightKeyDown_  = false;
                break;
            case ::Qt::Key_Up:
                rotateDownKeyDown_   = false;      // Inversion.
                break;
            case ::Qt::Key_Down:
                rotateUpKeyDown_     = false;        // Inversion.
                break;
            case ::Qt::Key_Q:
                rollLeftKeyDown_     = false;
                break;
            case ::Qt::Key_E:
                rollRightKeyDown_    = false;
                break;
            case ::Qt::Key_Shift:
                slowKeyDown_         = false;
                break;
            default:
                QOpenGLWidget::keyReleaseEvent(event);
                break;
        }

        UpdateKeyNavigation();

    }  else {
        QOpenGLWidget::keyPressEvent(event);
    }
}

void Viewer::OnTimer() {
    if (currentMoveSpeedMPerS_ || currentStrafeSpeedLeftRightMPerS_ || currentStrafeSpeedUpDownMPerS_
            || currentRotateSpeedLeftRightDegreesPerS_ || currentRotateSpeedUpDownDegreesPerS_
            || currentRollSpeedDegreesPerS_) {
        if (camera_) {
            float deltaS     { static_cast<float>(timerStopWatch_.DeltaMs()) / 1000.0f };
            float slowFactor { slowKeyDown_ ? slowFactor_ : 1.0f };

            Transform<float> transform;
            camera_->GetTransform(&transform);

            if (currentMoveSpeedMPerS_) {
                transform.Prepend(Transform<float>{(deltaS * *currentMoveSpeedMPerS_ * slowFactor)
                                                       * Vector<float>{0.0f, 0.0f, -1.0f}});
            }

            if (currentStrafeSpeedLeftRightMPerS_) {
                transform.Prepend(Transform<float>{(deltaS * *currentStrafeSpeedLeftRightMPerS_ * slowFactor)
                                                       * Vector<float>{1.0f, 0.0f, 0.0f}});
            }

            if (currentStrafeSpeedUpDownMPerS_) {
                transform.Prepend(Transform<float>{(deltaS * *currentStrafeSpeedUpDownMPerS_ * slowFactor)
                                                       * Vector<float>{0.0f, 1.0f, 0.0f}});
            }

            if (currentRotateSpeedLeftRightDegreesPerS_) {
                transform.Prepend(Transform<float>{Axis::Y,
                                                   deltaS * *currentRotateSpeedLeftRightDegreesPerS_ * slowFactor});
            }

            if (currentRotateSpeedUpDownDegreesPerS_) {
                transform.Prepend(Transform<float>{Axis::X,
                                                   deltaS * *currentRotateSpeedUpDownDegreesPerS_ * slowFactor});
            }

            if (currentRollSpeedDegreesPerS_) {
                transform.Prepend(Transform<float>{Axis::Z, deltaS * *currentRollSpeedDegreesPerS_ * slowFactor});
            }

            camera_->SetTransform(transform);
            update();
            emit CameraUpdated();
        }
    }
}

void Viewer::OnGLContextAboutToBeDestroyed() {
    makeCurrent();
    context_->ReleaseOpenGLResources();
}

void Viewer::SetViewPort() {
    Log::Print(Log::Level::Debug, this, [&]{ return "viewport_size=" + to_string(width_) + "x" + to_string(height_); });

    if (projection_) {
        projection_->SetViewPort(width_, height_);
        if (gui_) {
            float windowWidth;
            float windowHeight;
            projection_->GetWindowDimensions(&windowWidth, &windowHeight);
            float scaling     { (projection_->EyepointDistance() + guiDeltaZ_) / projection_->EyepointDistance() };
            float frameWidth  { scaling * windowWidth };
            float frameHeight { scaling * windowHeight };

            Position position{-.5f * frameWidth, .5f * frameHeight};
            Size     size{frameWidth, frameHeight};
            gui_->SetFrame(Frame(position, size), true);
        }

        update();

        emit ProjectionUpdated();
    }
}

void Viewer::UpdateKeyNavigation() {
    if (cameraNavigationEnabled_ && !rotating_) {
        if (moveForwardKeyDown_ == moveBackwardKeyDown_) {
            currentMoveSpeedMPerS_ = nullopt;
        } else if (moveForwardKeyDown_) {
            currentMoveSpeedMPerS_ = moveSpeedMPerS_;
        } else if (moveBackwardKeyDown_) {
            currentMoveSpeedMPerS_ = -moveSpeedMPerS_;
        }

        if (strafeLeftKeyDown_ == strafeRightKeyDown_) {
            currentStrafeSpeedLeftRightMPerS_ = nullopt;
        } else if (strafeLeftKeyDown_) {
            currentStrafeSpeedLeftRightMPerS_ = -moveSpeedMPerS_;
        } else if (strafeRightKeyDown_) {
            currentStrafeSpeedLeftRightMPerS_ = moveSpeedMPerS_;
        }

        if (strafeUpKeyDown_ == strafeDownKeyDown_) {
            currentStrafeSpeedUpDownMPerS_ = nullopt;
        } else if (strafeUpKeyDown_) {
            currentStrafeSpeedUpDownMPerS_ = moveSpeedMPerS_;
        } else if (strafeDownKeyDown_) {
            currentStrafeSpeedUpDownMPerS_ = -moveSpeedMPerS_;
        }

        if (rotateLeftKeyDown_ == rotateRightKeyDown_) {
            currentRotateSpeedLeftRightDegreesPerS_ = nullopt;
        } else if (rotateLeftKeyDown_) {
            currentRotateSpeedLeftRightDegreesPerS_ = rotateSpeedDegreesPerS_;
        } else if (rotateRightKeyDown_) {
            currentRotateSpeedLeftRightDegreesPerS_ = -rotateSpeedDegreesPerS_;
        }

        if (rotateUpKeyDown_ == rotateDownKeyDown_) {
            currentRotateSpeedUpDownDegreesPerS_ = nullopt;
        } else if (rotateUpKeyDown_) {
            currentRotateSpeedUpDownDegreesPerS_ = rotateSpeedDegreesPerS_;
        } else if (rotateDownKeyDown_) {
            currentRotateSpeedUpDownDegreesPerS_ = -rotateSpeedDegreesPerS_;
        }

        if (rollLeftKeyDown_ == rollRightKeyDown_) {
            currentRollSpeedDegreesPerS_ = nullopt;
        } else if (rollLeftKeyDown_) {
            currentRollSpeedDegreesPerS_ = rotateSpeedDegreesPerS_;
        } else if (rollRightKeyDown_) {
            currentRollSpeedDegreesPerS_ = -rotateSpeedDegreesPerS_;
        }
    } else {
        currentMoveSpeedMPerS_                  = nullopt;
        currentStrafeSpeedLeftRightMPerS_       = nullopt;
        currentStrafeSpeedUpDownMPerS_          = nullopt;
        currentRotateSpeedLeftRightDegreesPerS_ = nullopt;
        currentRotateSpeedUpDownDegreesPerS_    = nullopt;
        currentRollSpeedDegreesPerS_            = nullopt;
    }
    
    bool timerNeeded { currentMoveSpeedMPerS_.has_value()
                           || currentStrafeSpeedLeftRightMPerS_.has_value()
                           || currentStrafeSpeedUpDownMPerS_.has_value()
                           || currentRotateSpeedLeftRightDegreesPerS_.has_value()
                           || currentRotateSpeedUpDownDegreesPerS_.has_value()
                           || currentRollSpeedDegreesPerS_.has_value()};
    if (timerNeeded && !timer_->isActive()) {
        timer_->start();
        (void) timerStopWatch_.DeltaMs();
    } else if (!timerNeeded && timer_->isActive()) {
        timer_->stop();
    }
}

}    // Namespace Qt.
}    // Namespace Gui.
}    // Namespace Vectoid.
