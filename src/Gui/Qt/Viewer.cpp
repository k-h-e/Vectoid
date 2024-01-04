///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Gui/Qt/Viewer.h>

#include <QMouseEvent>
#include <QOpenGLContext>
#include <QWheelEvent>
#include <K/Core/NumberTools.h>
#include <K/Core/Log.h>
#include <Vectoid/SceneGraph/Camera.h>
#include <Vectoid/SceneGraph/PerspectiveProjection.h>
#include <Vectoid/SceneGraph/OpenGL/Context.h>
#include <Vectoid/SceneGraph/OpenGL/RenderTarget.h>

using std::make_shared;
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

namespace Vectoid {
namespace Gui {
namespace Qt {

Viewer::Viewer(QWidget *parent)
        : QOpenGLWidget(parent),
          qtGLContext_(nullptr),
          width_(1),
          height_(1),
          rotating_(false),
          panning_(false),
          movingRolling_(false),
          dragging_(false),
          mouseMovedWhilePressed_(false),
          cameraNavigationEnabled_(true),
          altKeyDown_(false),
          controlKeyDown_(false) {
    setMouseTracking(true);
    setFocusPolicy(::Qt::ClickFocus);

    context_      = make_shared<Context>();
    renderTarget_ = make_shared<class RenderTarget>(context_);
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
    root_       = root;
    projection_ = projection;
    camera_     = camera;

    renderTarget_->SetSceneGraph(root_);
    if (projection_) {
        projection_->SetViewPort(width_, height_);
        emit ProjectionUpdated();
    }

    update();
}

void Viewer::EnableCameraNavigation(bool enabled) {
    cameraNavigationEnabled_ = enabled;
    rotating_ = false;
    panning_  = false;
    dragging_ = false;
}

void Viewer::initializeGL() {
    qtGLContext_ = context();
    assert(qtGLContext_);
    connect(qtGLContext_, &QOpenGLContext::aboutToBeDestroyed, this, &Viewer::OnGLContextAboutToBeDestroyed);
    context_->InitializeGL();
}

void Viewer::paintGL() {
    renderTarget_->RenderFrame();
}

void Viewer::resizeGL(int width, int height) {
    NumberTools::ClampMin(&width, 1);
    NumberTools::ClampMin(&height, 1);
    width_  = width;
    height_ = height;
    if (root_ && projection_) {
        projection_->SetViewPort(width_, height_);
        emit ProjectionUpdated();
    }
    Log::Print(Log::Level::Debug, this, [&]{ return "viewport_size=" + to_string(width_) + "x" + to_string(height_); });
}

void Viewer::mousePressEvent(QMouseEvent *event) {
    rotating_      = false;
    panning_       = false;
    movingRolling_ = false;
    dragging_      = false;

    if (cameraNavigationEnabled_) {
        if (camera_) {
            camera_->GetTransform(&startCameraTransform_);
            if (altKeyDown_) {
                panning_ = true;
            } else if (controlKeyDown_) {
                movingRolling_ = true;
            } else {
                rotating_ = true;
            }
        }
    } else {
        dragging_ = true;
    }

    if (rotating_ || panning_ || movingRolling_ || dragging_) {
        startX_                 = event->pos().x();
        startY_                 = event->pos().y();
        mouseMovedWhilePressed_ = false;

        if (dragging_) {
            emit MouseDragStateChanged(true);
        }
    }
}

void Viewer::mouseReleaseEvent(QMouseEvent *event) {
    (void)event;

    bool didDrag = dragging_;

    rotating_      = false;
    panning_       = false;
    movingRolling_ = false;
    dragging_      = false;

    if (didDrag) {
        emit MouseDragStateChanged(false);
    }
    if (!mouseMovedWhilePressed_) {
        emit MouseClicked();
    }
}

void Viewer::mouseMoveEvent(QMouseEvent *event) {
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
        } else if (panning_) {
            if (camera_) {
                Transform<float> cameraRotation = startCameraTransform_;
                cameraRotation.SetTranslationPart(Vector<float>(0.0f, 0.0f, 0.0f));
                Vector<float> up(0.0f, 1.0f, 0.0f);
                cameraRotation.ApplyTo(&up);
                Vector<float> right(1.0f, 0.0f, 0.0f);
                cameraRotation.ApplyTo(&right);

                Vector<float> position;
                startCameraTransform_.GetTranslationPart(&position);
                position = position - 20.0f*(current.x - start.x)*right - 20.0f*(current.y - start.y)*up;
                camera_->SetPosition(position);
                update();
                emit CameraUpdated();
            }
        } else if (movingRolling_) {
            if (camera_) {
                Transform<float> transform = startCameraTransform_;
                transform.Prepend(Transform<float>((100.0f * (current.y - start.y)/projection_->WindowSize())
                                                      * Vector<float>(0.0f, 0.0f, 1.0f)));
                transform.Prepend(Transform<float>(Axis::Z, 90.0f * (current.x - start.x)/projection_->WindowSize()));
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

void Viewer::keyPressEvent(QKeyEvent *event) {
    switch (event->key()) {
        case ::Qt::Key_Alt:
            altKeyDown_ = true;
            break;
        case ::Qt::Key_Meta:
            controlKeyDown_ = true;
            break;
        default:
            QOpenGLWidget::keyPressEvent(event);
            break;
    }
}

void Viewer::keyReleaseEvent(QKeyEvent *event) {
    switch (event->key()) {
        case ::Qt::Key_Alt:
            altKeyDown_ = false;
            break;
        case ::Qt::Key_Meta:
            controlKeyDown_ = false;
            break;
        default:
            QOpenGLWidget::keyReleaseEvent(event);
            break;
    }
}

void Viewer::OnGLContextAboutToBeDestroyed() {
    makeCurrent();
    context_->ReleaseOpenGLResources();
}

}    // Namespace Qt.
}    // Namespace Gui.
}    // Namespace Vectoid.
