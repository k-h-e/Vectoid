///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Gui/Button.h>

#include <K/Core/Log.h>
#include <K/Core/NumberTools.h>
#include <Vectoid/Gui/Context.h>
#include <Vectoid/Gui/TouchInfo.h>
#include <Vectoid/SceneGraph/CoordSys.h>
#include <Vectoid/SceneGraph/Geode.h>
#include <Vectoid/SceneGraph/RenderTargetInterface.h>
#include <Vectoid/SceneGraph/TextConsole.h>

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

Button::Button(const string &text, const Size &glyphSize, const shared_ptr<Context> &context)
        : GuiElement{context},
          handler_{nullptr},
          touchInside_{false} {
    int width = static_cast<int>(text.size());
    NumberTools::ClampMin(&width, 1);
    textConsole_ = context_->renderTarget->NewTextConsole(width, 1, glyphSize.width, glyphSize.height,
                                                          context_->glyphs);
    textConsole_->SetFrameWidth(context_->frameWidth);
    textConsole_->EnableFrame(true);
    textConsole_->WriteAt(0, 0, text.c_str(), TextConsole::Color::Custom);
    coordSys_    = context_->renderTarget->NewCoordSys();
    coordSys_->AddChild(context_->renderTarget->NewGeode(textConsole_));
              
    SetColors(false);
}

void Button::Register(HandlerInterface *handler) {
    handler_ = handler;
}

void Button::AddSceneGraphNodes(CoordSys *guiCoordSys) {
    guiCoordSys->AddChild(coordSys_);
}

Size Button::UpdateRequiredSizes() {
    Vector<float> extents = textConsole_->BoundingBox().Extents();
    requiredSize_.width  = extents.x;
    requiredSize_.height = extents.y;
    return requiredSize_;
}

void Button::Layout(const Frame &frame) {
    frame_.position = frame.position;
    frame_.size     = requiredSize_;
    coordSys_->SetPosition(Vector<float>(frame_.position.x + .5f*frame_.size.width,
                                         frame_.position.y - .5f*frame_.size.height,
                                         0.0f));
    context_->RequestRedraw();
}

GuiElement *Button::TouchedElement(const TouchInfo &touch) {
    return frame_.Contains(touch.x, touch.y) ? this : nullptr;
}

void Button::OnTouchGestureBegan(const vector<const TouchInfo *> &touches) {
    touchInside_ = true;
    SetColors(true);
    context_->RequestRedraw();
}

void Button::OnTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    if (touches.size() == 1u) {
        touchInside_ = frame_.Contains(touches[0]->x, touches[0]->y);
        SetColors(touchInside_);
        context_->RequestRedraw();
    }
}

void Button::OnTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    bool inside = touchInside_;
    
    touchInside_ = false;
    SetColors(false);
    context_->RequestRedraw();
    
    if (inside) {
        if (handler_) {
            handler_->OnButtonPressed(this);
        }
    }
}

void Button::SetColors(bool active) {
    if (active) {
        textConsole_->SetBackgroundColor(context_->selectionBackgroundColor, 1.0f);
        textConsole_->SetCustomColor(context_->selectionTextColor);
        textConsole_->SetFrameColor(.6f * context_->selectionTextColor);
    } else {
        textConsole_->SetBackgroundColor(context_->menuBackgroundColor, context_->menuBackgroundAlpha);
        textConsole_->SetCustomColor(context_->menuTextColor);
        textConsole_->SetFrameColor(.6f * context_->menuTextColor);
    }
}
    
}    // Namespace Gui.
}    // Namespace Vectoid.
