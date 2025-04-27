///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Gui/CustomButton.h>

#include <K/Core/Log.h>
#include <K/Core/NumberTools.h>
#include <Vectoid/Core/BoundingBox.h>
#include <Vectoid/Gui/Context.h>
#include <Vectoid/Gui/CustomContentInterface.h>
#include <Vectoid/Gui/TouchInfo.h>
#include <Vectoid/SceneGraph/CoordSys.h>
#include <Vectoid/SceneGraph/CustomPanel.h>
#include <Vectoid/SceneGraph/Geode.h>
#include <Vectoid/SceneGraph/RenderTargetInterface.h>

using std::nullopt;
using std::shared_ptr;
using std::string;
using std::vector;
using K::Core::Log;
using K::Core::NumberTools;
using Vectoid::Core::Vector;
using Vectoid::SceneGraph::CoordSys;
using Vectoid::SceneGraph::TextConsole;

namespace Vectoid {
namespace Gui {

CustomButton::CustomButton(const shared_ptr<CustomContentInterface> &content, const shared_ptr<Context> &context)
        : GuiElement{context},
          handler_{nullptr},
          content_{content},
          touchInside_{false},
          animationEnabled_{false} {
    panel_    = context_->renderTarget->NewCustomPanel(content_->Size().width + context_->glyphSize.width,
                                                       content_->Size().height + context_->glyphSize.width);
    panel_->SetFrameWidth(context_->frameWidth);
    panel_->EnableFrame(true);
    coordSys_ = context_->renderTarget->NewCoordSys();
    coordSys_->AddChild(context_->renderTarget->NewGeode(panel_));
    content_->AddSceneGraphNodes(coordSys_.get());
    
    SetColors();
}

void CustomButton::Register(HandlerInterface *handler) {
    handler_ = handler;
}

void CustomButton::EnableAnimation(bool enabled) {
    animationEnabled_ = enabled;
    context_->RequestCyclicUpdateCalls(this, animationEnabled_);
    if (!animationEnabled_) {
        content_->ResetAnimation();
        context_->RequestRedraw();
    }
}

void CustomButton::SetCustomColors(const Vector<float> &foregroundColor, const Vector<float> &backgroundColor) {
    foregroundColor_ = foregroundColor;
    backgroundColor_ = backgroundColor;
    SetColors();
    context_->RequestRedraw();
}

void CustomButton::ClearCustomColors() {
    foregroundColor_ = nullopt;
    backgroundColor_ = nullopt;
    SetColors();
    context_->RequestRedraw();
}

void CustomButton::AddSceneGraphNodes(CoordSys *guiCoordSys) {
    guiCoordSys->AddChild(coordSys_);
}

RequiredSize CustomButton::UpdateRequiredSizes() {
    Vector<float> extents = panel_->BoundingBox().Extents();
    requiredSize_.size.width  = extents.x;
    requiredSize_.size.height = extents.y;
    return requiredSize_;
}

void CustomButton::Layout(const Frame &frame) {
    if (verticalAlignment_ == VerticalAlignment::Bottom) {
        float y { frame.position.y - frame.size.height + requiredSize_.size.height };
        NumberTools::ClampMax(y, frame.position.y);
        frame_.position.y = y;
        frame_.position.x = frame.position.x;
    } else {
        frame_.position = frame.position;
    }
    frame_.size = requiredSize_.size;
    coordSys_->SetPosition(Vector<float>(frame_.position.x + .5f*frame_.size.width,
                                         frame_.position.y - .5f*frame_.size.height,
                                         0.0f));
    context_->RequestRedraw();
}

void CustomButton::OnCyclicUpdate(float deltaTimeS) {
    if (animationEnabled_) {
        content_->Animate(deltaTimeS);
        context_->RequestRedraw();
    }
}

GuiElement *CustomButton::TouchedElement(const TouchInfo &touch) {
    return frame_.Contains(touch.x, touch.y) ? this : nullptr;
}

void CustomButton::OnTouchGestureBegan(const vector<const TouchInfo *> &touches) {
    (void) touches;
    touchInside_ = true;
    SetColors();
    context_->RequestRedraw();
}

void CustomButton::OnTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    if (touches.size() == 1u) {
        touchInside_ = frame_.Contains(touches[0]->x, touches[0]->y);
        SetColors();
        context_->RequestRedraw();
    }
}

void CustomButton::OnTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    (void) touches;

    bool inside = touchInside_;
    
    touchInside_ = false;
    SetColors();
    context_->RequestRedraw();
    
    if (inside) {
        if (handler_) {
            handler_->OnCustomButtonPressed(this);
        }
    }
}

void CustomButton::SetColors() {
    if (touchInside_) {
        panel_->SetBackgroundColor(context_->selectionBackgroundColor, 1.0f);
        content_->SetColor(context_->selectionTextColor);
        panel_->SetFrameColor(.6f * context_->selectionTextColor);
    } else {
        Vector<float> foregroundColor = foregroundColor_ ? *foregroundColor_ : context_->menuTextColor;
        Vector<float> backgroundColor = backgroundColor_ ? *backgroundColor_ : context_->menuBackgroundColor;
        panel_->SetBackgroundColor(backgroundColor, context_->menuBackgroundAlpha);
        content_->SetColor(foregroundColor);
        panel_->SetFrameColor(.6f * context_->menuTextColor);
    }
}
    
}    // Namespace Gui.
}    // Namespace Vectoid.
