#include <Vectoid/Gui/CustomButton.h>

#include <K/Core/Log.h>
#include <K/Core/NumberTools.h>
#include <Vectoid/Gui/Context.h>
#include <Vectoid/Gui/CustomContentInterface.h>
#include <Vectoid/Gui/TouchInfo.h>
#include <Vectoid/SceneGraph/CoordSys.h>
#include <Vectoid/SceneGraph/CustomPanel.h>
#include <Vectoid/SceneGraph/Geode.h>
#include <Vectoid/SceneGraph/RenderTargetInterface.h>

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
    coordSys_ = context_->renderTarget->NewCoordSys();
    coordSys_->AddChild(context_->renderTarget->NewGeode(panel_));
    content_->AddSceneGraphNodes(coordSys_.get());
    
    SetColors(false);
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

void CustomButton::AddSceneGraphNodes(CoordSys *guiCoordSys) {
    guiCoordSys->AddChild(coordSys_);
}

Size CustomButton::UpdateRequiredSizes() {
    requiredSize_.width  = panel_->Width();
    requiredSize_.height = panel_->Height();
    return requiredSize_;
}

void CustomButton::Layout(const Frame &frame) {
    frame_.position = frame.position;
    frame_.size     = requiredSize_;
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
    touchInside_ = true;
    SetColors(true);
    context_->RequestRedraw();
}

void CustomButton::OnTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    if (touches.size() == 1u) {
        touchInside_ = frame_.Contains(touches[0]->x, touches[0]->y);
        SetColors(touchInside_);
        context_->RequestRedraw();
    }
}

void CustomButton::OnTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    bool inside = touchInside_;
    
    touchInside_ = false;
    SetColors(false);
    context_->RequestRedraw();
    
    if (inside) {
        if (handler_) {
            handler_->OnCustomButtonPressed(this);
        }
    }
}

void CustomButton::SetColors(bool active) {
    if (active) {
        panel_->SetBackgroundColor(context_->selectionBackgroundColor, 1.0f);
        content_->SetColor(context_->selectionTextColor);
    } else {
        panel_->SetBackgroundColor(context_->menuBackgroundColor, context_->menuBackgroundAlpha);
        content_->SetColor(context_->menuTextColor);
    }
}
    
}    // Namespace Gui.
}    // Namespace Vectoid.
