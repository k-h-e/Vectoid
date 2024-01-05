///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/PerspectiveProjection.h>

using std::shared_ptr;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {

const float PerspectiveProjection::paramMin = 0.0001f;

PerspectiveProjection::PerspectiveProjection(const shared_ptr<Context> &context)
        : GroupNode(context),
          eyepointDistance_(paramMin),
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

void PerspectiveProjection::GetWindowDimensions(float *outWidth, float *outHeight) const {
    bool assignWindowSizeToWidth = (width_ < height_);
    if (windowSizeIsLargerViewPortDimension_) {
        assignWindowSizeToWidth = !assignWindowSizeToWidth;
    }
    if (assignWindowSizeToWidth) {
        *outWidth  = windowSize_;
        *outHeight = windowSize_ * height_ / width_;
    }
    else {
        *outWidth  = windowSize_ * width_ / height_;
        *outHeight = windowSize_;
    }
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
    GetWindowDimensions(&windowWidth, &windowHeight);
    return Vector<float>((x/width_ - .5f)  * windowWidth, (.5f - y/height_) * windowHeight, 0.0f);
}

Vector<float> PerspectiveProjection::TransformViewPortCoordinates(float x, float y, float cameraZ) const {
    return ((eyepointDistance_ - cameraZ) / eyepointDistance_) * TransformViewPortCoordinates(x, y);
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
