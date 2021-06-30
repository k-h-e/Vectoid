#include <Vectoid/UI/Qt/Viewer.h>

#include <QMouseEvent>
#include <QWheelEvent>
#include <K/Core/NumberTools.h>
#include <K/Core/Log.h>
#include <Vectoid/SceneGraph/Camera.h>
#include <Vectoid/SceneGraph/PerspectiveProjection.h>
#include <Vectoid/SceneGraph/OpenGL/RenderTarget.h>

using std::shared_ptr;
using std::to_string;
using K::Core::NumberTools;
using K::Core::Log;
using Vectoid::Core::Axis;
using Vectoid::Core::Vector;
using Vectoid::Core::Transform;
using Vectoid::SceneGraph::RenderTargetInterface;
using Vectoid::SceneGraph::Node;
using Vectoid::SceneGraph::PerspectiveProjection;
using Vectoid::SceneGraph::Camera;

namespace Vectoid {
namespace UI {
namespace Qt {

Viewer::Viewer(QWidget *parent)
        : QOpenGLWidget(parent),
          renderTarget_(new Vectoid::SceneGraph::OpenGL::RenderTarget()),
          width_(1),
          height_(1),
          rotating_(false) {
    // Nop.
}

shared_ptr<RenderTargetInterface> Viewer::RenderTarget() {
    return renderTarget_;
}

void Viewer::SetSceneGraph(const shared_ptr<Node> &root, const shared_ptr<PerspectiveProjection> &projection,
                           const shared_ptr<Camera> &camera) {
    root_       = root;
    projection_ = projection;
    camera_     = camera;

    renderTarget_->SetSceneGraph(root_);
    if (projection_) {
        projection_->SetViewPort(width_, height_);
    }

    update();
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
    }
    Log::Print(Log::Level::Debug, this, [&]{ return "viewport_size=" + to_string(width_) + "x" + to_string(height_); });
}

void Viewer::mousePressEvent(QMouseEvent *event) {
    if (!rotating_ && !panning_ && camera_) {
        startX_ = event->x();
        startY_ = event->y();
        camera_->GetTransform(&startCameraTransform_);
        if (event->button() == ::Qt::LeftButton) {
            rotating_ = true;
        }
        else if (event->button() == ::Qt::RightButton) {
            panning_ = true;
        }
    }
}

void Viewer::mouseReleaseEvent(QMouseEvent *event) {
    (void)event;
    rotating_ = false;
    panning_  = false;
}

void Viewer::mouseMoveEvent(QMouseEvent *event) {
    int x = event->x();
    int y = event->y();
    if ((rotating_ || panning_) && projection_ && camera_) {
        Vector<float> start = projection_->TransformViewPortCoordinates(static_cast<float>(startX_),
                                                                        static_cast<float>(startY_));
        Vector<float> stop  = projection_->TransformViewPortCoordinates(static_cast<float>(x),
                                                                        static_cast<float>(y));
        if (rotating_) {
            float yawAngle   =  (stop.x - start.x)/projection_->WindowSize() * 90.0f;
            float pitchAngle = -(stop.y - start.y)/projection_->WindowSize() * 90.0f;
            Transform<float> transform = startCameraTransform_;
            transform.Prepend(Transform(Axis::Y, yawAngle));
            transform.Prepend(Transform(Axis::X, pitchAngle));
            camera_->SetTransform(transform);
            update();

        } else if (panning_) {
            Transform<float> cameraRotation = startCameraTransform_;
            cameraRotation.SetTranslationPart(Vector<float>(0.0f, 0.0f, 0.0f));
            Vector<float> up(0.0f, 1.0f, 0.0f);
            cameraRotation.ApplyTo(&up);
            Vector<float> right(1.0f, 0.0f, 0.0f);
            cameraRotation.ApplyTo(&right);

            Vector<float> position;
            startCameraTransform_.GetTranslationPart(&position);
            position = position - 15.0f*(stop.x - start.x)*right - 15.0f*(stop.y - start.y)*up;
            camera_->SetPosition(position);
            update();
        }
    }
}

void Viewer::wheelEvent(QWheelEvent *event) {
    if (projection_ && camera_) {
        Vector position(0.0f, 0.0f, .01f * static_cast<float>(event->angleDelta().y()) * projection_->WindowSize());
        Transform<float> transform;
        camera_->GetTransform(&transform);
        transform.ApplyTo(&position);
        transform.SetTranslationPart(position);

        float rollAngle = -.02f * static_cast<float>(event->angleDelta().x());
        transform.Prepend(Transform<float>(Axis::Z, rollAngle));

        camera_->SetTransform(transform);
        update();
    }
}

}    // Namespace Qt.
}    // Namespace UI.
}    // Namespace Vectoid.
