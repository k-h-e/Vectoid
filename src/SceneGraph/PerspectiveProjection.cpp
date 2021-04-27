#include <Vectoid/SceneGraph/PerspectiveProjection.h>

#include <Vectoid/SceneGraph/VisitorInterface.h>

using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {

const float PerspectiveProjection::paramMin = 0.0001f;

PerspectiveProjection::PerspectiveProjection()
        : eyepointDistance_(paramMin),
          viewingDepth_(paramMin),
          windowSize_(paramMin),
          windowSizeIsLargerViewPortDimension_(true) {
    SetViewPort(1.0f, 1.0f);    // Sets parametersChanged_ to true.
}

void PerspectiveProjection::SetWindowSize(float windowSize, bool identifyWithLargerViewPortDimension) {
    if (windowSize >= paramMin) {
        windowSize_                          = windowSize;
        windowSizeIsLargerViewPortDimension_ = identifyWithLargerViewPortDimension;
        parametersChanged_                   = true;
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

Vector<float> PerspectiveProjection::TransformViewPortCoordinates(float x, float y) const {
    float windowWidth, windowHeight;
    ComputeWindowDimensions(&windowWidth, &windowHeight);
    return Vector<float>((x/width_ - .5f)  * windowWidth, (.5f - y/height_) * windowHeight, 0.0f);
}

void PerspectiveProjection::ComputeWindowDimensions(float *width, float *height) const {
    bool assignWindowSizeToWidth = (width_ < height_);
    if (windowSizeIsLargerViewPortDimension_) {
        assignWindowSizeToWidth = !assignWindowSizeToWidth;
    }
    if (assignWindowSizeToWidth) {
        *width  = windowSize_;
        *height = windowSize_ * height_ / width_;
    }
    else {
        *width  = windowSize_ * width_ / height_;
        *height = windowSize_;
    }
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
