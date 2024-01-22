///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/CustomPanel.h>

#include <K/Core/NumberTools.h>
#include <Vectoid/Core/BoundingBox.h>

using std::shared_ptr;
using K::Core::NumberTools;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {

CustomPanel::CustomPanel(const shared_ptr<Context> &context, float width, float height)
        : Geometry{context},
          width_{width},
          height_{height},
          frameWidth_{.01f},
          backgroundAlpha_{1.0f},
          frameColor_{1.0f, 1.0f, 1.0f},
          frameEnabled_{false} {
    NumberTools::ClampMin(&width_, 0.0f);
    NumberTools::ClampMin(&height_, 0.0f);
}

Core::BoundingBox<float> CustomPanel::BoundingBox() const {
    Core::BoundingBox<float> box;
    box.Grow(Vector<float>(-.5f * width_, -.5f * height_, 0.0f));
    box.Grow(Vector<float>( .5f * width_,  .5f * height_, 0.0f));
    if (frameEnabled_) {
        box.Expand(frameWidth_);
    }
    return box;
}

void CustomPanel::SetBackgroundColor(const Vector<float> &color, float alpha) {
    backgroundColor_ = color;
    NumberTools::Clamp(&backgroundColor_.x, 0.0f, 1.0f);
    NumberTools::Clamp(&backgroundColor_.y, 0.0f, 1.0f);
    NumberTools::Clamp(&backgroundColor_.z, 0.0f, 1.0f);

    backgroundAlpha_ = alpha;
    NumberTools::Clamp(&backgroundAlpha_, 0.0f, 1.0f);
}

void CustomPanel::EnableFrame(bool enabled) {
    frameEnabled_ = enabled;
}

void CustomPanel::SetFrameColor(const Vector<float> &color) {
    frameColor_ = color;
    NumberTools::Clamp(&frameColor_.x, 0.0f, 1.0f);
    NumberTools::Clamp(&frameColor_.y, 0.0f, 1.0f);
    NumberTools::Clamp(&frameColor_.z, 0.0f, 1.0f);
}

void CustomPanel::SetFrameWidth(float width) {
    if (!(width > 0.0f)) {
        width = .01f;
    }

    frameWidth_ = width;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
