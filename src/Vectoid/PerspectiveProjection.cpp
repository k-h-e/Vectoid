#include <kxm/Vectoid/PerspectiveProjection.h>

#include <kxm/Vectoid/OpenGL.h>

namespace kxm {
namespace Vectoid {

const float PerspectiveProjection::paramMin = 0.0001f;

PerspectiveProjection::PerspectiveProjection()
        : windowSize_(paramMin),
          eyepointDistance_(paramMin),
          viewingDepth_(paramMin) {
    SetViewPort(1.0f, 1.0f);    // Sets parametersChanged_ to true.
}

void PerspectiveProjection::SetWindowSize(float windowSize) {
    if (windowSize >= paramMin) {
        windowSize_        = windowSize;
        parametersChanged_ = true;
    }
}
float PerspectiveProjection::WindowSize() const {
    return windowSize_;
}

void PerspectiveProjection::SetViewingDepth(float viewingDepth) {
    if (viewingDepth >= paramMin) {
        viewingDepth_      = viewingDepth;
        parametersChanged_ = true;
    } 
}
float PerspectiveProjection::ViewingDepth() const {
    return viewingDepth_;
}

void PerspectiveProjection::SetEyepointDistance(float eyepointDistance) {
    if (eyepointDistance >= paramMin) {
        eyepointDistance_  = eyepointDistance;
        parametersChanged_ = true;
    } 
}
float PerspectiveProjection::EyepointDistance() const {
    return eyepointDistance_;
}

void PerspectiveProjection::SetViewPort(float width, float height) {
    if ((width < 1.0f) || (height < 1.0f)) {
        width =  1.0f;
        height = 1.0f;
    }
    width_             = width;
    height_            = height;
    parametersChanged_ = true;
}

Vector PerspectiveProjection::TransformViewPortCoordinates(float x, float y) const {
    float windowWidth, windowHeight;
    ComputeWindowDimensions(&windowWidth, &windowHeight);
    return Vector((x/width_ - .5f)  * windowWidth,
                  (.5f - y/height_) * windowHeight,
                  0.0f);
}

void PerspectiveProjection::Render(RenderContext *context) {
    if (parametersChanged_) {
        float windowWidth, windowHeight;
        ComputeWindowDimensions(&windowWidth, &windowHeight);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
#ifdef KXM_VECTOID_GLES
        glFrustumf(-windowWidth  / 2.0f, windowWidth  / 2.0f,
                   -windowHeight / 2.0f, windowHeight / 2.0f,
                    eyepointDistance_, eyepointDistance_ + viewingDepth_);
#else
        glFrustum(-windowWidth  / 2.0f, windowWidth  / 2.0f,
                  -windowHeight / 2.0f, windowHeight / 2.0f,
                   eyepointDistance_, eyepointDistance_ + viewingDepth_);
#endif
        glTranslatef(0.0, 0.0, -eyepointDistance_);
        glMatrixMode(GL_MODELVIEW);
        parametersChanged_ = false;
    }
    SceneGraphNode::Render(context);
}

void PerspectiveProjection::ComputeWindowDimensions(float *width, float *height) const {
    if (width_ > height_) {
        *width  = windowSize_;
        *height = windowSize_ * height_ / width_;
    }
    else {
        *width  = windowSize_ * width_ / height_;
        *height = windowSize_;
    }
}

}    // Namespace Vectoid.
}    // Namespace kxm.
