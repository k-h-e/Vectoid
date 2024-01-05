///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/ComboBarrel.h>

#include <cassert>
#include <K/Core/Log.h>
#include <K/Core/NumberTools.h>
#include <Vectoid/Core/Transform.h>

using std::nullopt;
using std::optional;
using std::shared_ptr;
using std::string;
using std::to_string;
using K::Core::Log;
using K::Core::NumberTools;
using Vectoid::Core::BoundingBox;
using Vectoid::Core::Vector;
using Vectoid::Core::Transform;

namespace Vectoid {
namespace SceneGraph {

ComboBarrel::ComboBarrel(const shared_ptr<Context> &context, int width, int numVisibleOtherPerSide, float glyphWidth,
                         float glyphHeight, const shared_ptr<Glyphs> &glyphs)
        : Geometry{context},
          width_{width},
          numVisibleOtherPerSide_{numVisibleOtherPerSide},
          glyphWidth_{glyphWidth},
          glyphHeight_{glyphHeight},
          glyphs_{glyphs},
          position_{0.0f},
          backgroundColor_{1.0f, 1.0f, 1.0f},
          backgroundAlpha_{.125f},
          color_{1.0f, 1.0f, 1.0f},
          frameWidth_{0.25f * glyphWidth_},
          frameEnabled_{false} {
    assert(numVisibleOtherPerSide >= 1);
    itemAngle_    = 180.0f / (2.0f*static_cast<float>(numVisibleOtherPerSide) + 1.0f);
    barrelRadius_ = .5f * glyphHeight_ / sin(.5f * itemAngle_ / 180.0f * static_cast<float>(NumberTools::pi));
    for (int i = 0; i < 2*numVisibleOtherPerSide_ + 3; ++i) {
        float angle { static_cast<float>(i) * 180.0f / (2.0f * static_cast<float>(numVisibleOtherPerSide) + 1.0f) };
        Vector<float> hand { 0.0f, barrelRadius_, 0.0f };
        Transform<float> { Vectoid::Core::Axis::X, angle }.ApplyTo(&hand);
        yCoords_.push_back(hand.y);
        zCoords_.push_back(hand.z);
        boundingBox_.Grow(Vector<float>(-.5f * width_ * glyphWidth_, hand.y, hand.z));
        boundingBox_.Grow(Vector<float>( .5f * width_ * glyphWidth_, hand.y, hand.z));
        Log::Print(Log::Level::Debug, this, [&]{
            return "angle=" + to_string(angle) + ", hand=" + hand.ToString();
        });
    }
    boundingBox_.Expand(.5f * glyphWidth_, 0.0f, 0.0f);
}

void ComboBarrel::Clear() {
    items_.clear();
    position_ = 0.0f;
}

int ComboBarrel::AddItem(const string &item) {
    int index { static_cast<int>(items_.size()) };
    items_.push_back(item);
    return index;
}

optional<int> ComboBarrel::Selection() const {
    if (!items_.empty()) {
        if (position_ < 0.0f) {
            return 0;
        } else {
            int selection { static_cast<int>(position_ + .5f) };
            NumberTools::Clamp(&selection, 0, static_cast<int>(items_.size()) - 1);
            return selection;
        }
    } else {
        return nullopt;
    }
}

void ComboBarrel::SetSelection(int itemId) {
    if ((itemId >= 0) && (itemId < static_cast<int>(items_.size()))) {
        position_ = static_cast<float>(itemId);
    }
}

void ComboBarrel::SetPosition(float position) {
    if (!items_.empty()) {
        NumberTools::Clamp(&position, -.5f, static_cast<float>(items_.size()) - .5f);
        position_ = position;
    } else {
        position_ = 0.0f;
    }
}

float ComboBarrel::Position() const {
    return position_;
}

BoundingBox<float> ComboBarrel::BoundingBox() const {
    Vectoid::Core::BoundingBox<float> box { boundingBox_ };
    if (frameEnabled_) {
        box.Expand(frameWidth_);
    }
    return box;
}

void ComboBarrel::SetBackgroundColor(const Vector<float> &color, float alpha) {
    backgroundColor_ = color;
    NumberTools::Clamp(&backgroundColor_.x, 0.0f, 1.0f);
    NumberTools::Clamp(&backgroundColor_.y, 0.0f, 1.0f);
    NumberTools::Clamp(&backgroundColor_.z, 0.0f, 1.0f);

    backgroundAlpha_ = alpha;
    NumberTools::Clamp(&backgroundAlpha_, 0.0f, 1.0f);
}

void ComboBarrel::SetColor(const Vectoid::Core::Vector<float> &color) {
    color_ = color;
    NumberTools::Clamp(&color_.x, 0.0f, 1.0f);
    NumberTools::Clamp(&color_.y, 0.0f, 1.0f);
    NumberTools::Clamp(&color_.z, 0.0f, 1.0f);
}

void ComboBarrel::EnableFrame(bool enabled) {
    frameEnabled_ = enabled;
}

void ComboBarrel::SetFrameWidth(float width) {
    if (!(width > 0.0f)) {
        width = .125f * glyphWidth_;
    }
    
    frameWidth_ = width;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
