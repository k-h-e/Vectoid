///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Gui/ComboBarrel.h>

#include <Vectoid/Gui/Context.h>
#include <Vectoid/Gui/TouchInfo.h>
#include <Vectoid/SceneGraph/ComboBarrel.h>
#include <Vectoid/SceneGraph/CoordSys.h>
#include <Vectoid/SceneGraph/Geode.h>
#include <Vectoid/SceneGraph/RenderTargetInterface.h>

using std::make_shared;
using std::optional;
using std::shared_ptr;
using std::string;
using std::vector;
using Vectoid::Core::Vector;
using Vectoid::Gui::TouchInfo;
using Vectoid::SceneGraph::CoordSys;

namespace Vectoid {
namespace Gui {

struct TouchInfo;

ComboBarrel::ComboBarrel(int width, int numVisibleOtherPerSide, Size glyphSize, const shared_ptr<Context> &context)
        : GuiElement{context},
          handler_{nullptr},
          startPosition_{0.0f} {
    comboBarrel_ = context_->renderTarget->NewComboBarrel(width, numVisibleOtherPerSide, glyphSize.width,
                                                          glyphSize.height, context_->glyphs);
    comboBarrel_->SetFrameWidth(context_->frameWidth);
    comboBarrel_->EnableFrame(true);
    coordSys_    = context_->renderTarget->NewCoordSys();
    coordSys_->AddChild(context_->renderTarget->NewGeode(comboBarrel_));
              
    SetColors(false);
}

void ComboBarrel::Register(HandlerInterface *handler) {
    handler_ = handler;
}

void ComboBarrel::Clear() {
    comboBarrel_->Clear();
    context_->RequestRedraw();
}

int ComboBarrel::AddItem(const string &item) {
    int id = comboBarrel_->AddItem(item);
    context_->RequestRedraw();
    return id;
}

optional<int> ComboBarrel::Selection() const {
    return comboBarrel_->Selection();
}

void ComboBarrel::SetSelection(int itemId) {
    comboBarrel_->SetSelection(itemId);
    context_->RequestRedraw();
}

void ComboBarrel::AddSceneGraphNodes(CoordSys *guiCoordSys) {
    guiCoordSys->AddChild(coordSys_);
}

Size ComboBarrel::UpdateRequiredSizes() {
    Vector<float> extents = comboBarrel_->BoundingBox().Extents();
    requiredSize_.width  = extents.x;
    requiredSize_.height = extents.y;
    return requiredSize_;
}

void ComboBarrel::Layout(const Frame &frame) {
    frame_.position = frame.position;
    frame_.size     = requiredSize_;
    coordSys_->SetPosition(Vector<float>(frame_.position.x + .5f*frame_.size.width,
                                         frame_.position.y - .5f*frame_.size.height,
                                         0.0f));
    context_->RequestRedraw();
}

GuiElement *ComboBarrel::TouchedElement(const TouchInfo &touch) {
    return frame_.Contains(touch.x, touch.y) ? this : nullptr;
}

void ComboBarrel::OnTouchGestureBegan(const vector<const TouchInfo *> &touches) {
    startPosition_ = comboBarrel_->Position();
    SetColors(true);
    context_->RequestRedraw();
}

void ComboBarrel::OnTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    if (touches.size() == 1u) {
        optional<int> oldSelection = comboBarrel_->Selection();
        
        const TouchInfo &touch = *(touches[0]);
        float t = (touch.y - touch.startY) / frame_.size.height;
        comboBarrel_->SetPosition(startPosition_ + t*8.0f);
        context_->RequestRedraw();
        
        if (handler_) {
            optional<int> selection = comboBarrel_->Selection();
            if (selection && (!oldSelection || (*selection != *oldSelection))) {
                handler_->OnComboBarrelSelectionChanged(this, *selection);
            }
        }
    }
}

void ComboBarrel::OnTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    SetColors(false);
    context_->RequestRedraw();
}

void ComboBarrel::SetColors(bool active) {
    if (active) {
        comboBarrel_->SetBackgroundColor(context_->selectionBackgroundColor, 1.0f);
        comboBarrel_->SetColor(context_->selectionTextColor);
    } else {
        comboBarrel_->SetBackgroundColor(context_->menuBackgroundColor, context_->menuBackgroundAlpha);
        comboBarrel_->SetColor(context_->menuTextColor);
    }
}

}    // Namespace Gui.
}    // Namespace Vectoid.
