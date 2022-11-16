#include <Vectoid/Gui/Button.h>

#include <K/Core/Log.h>
#include <K/Core/NumberTools.h>
#include <Vectoid/Gui/Context.h>
#include <Vectoid/Gui/RedrawRequestHandlerInterface.h>
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

Button::Button(const string &text, float glyphWidth, float glyphHeight, const shared_ptr<Context> &context)
        : GuiElement{context},
          touchInside_{false} {
    int width = static_cast<int>(text.size());
    NumberTools::ClampMin(&width, 1);
    textConsole_ = context_->renderTarget->NewTextConsole(width, 1, glyphWidth, glyphHeight, context_->glyphs);
    textConsole_->WriteAt(0, 0, text.c_str(), TextConsole::Color::White);
    coordSys_    = context_->renderTarget->NewCoordSys();
    coordSys_->AddChild(context_->renderTarget->NewGeode(textConsole_));
              
    SetBackgroundColor(false);
}

void Button::AddSceneGraphNodes(const shared_ptr<CoordSys> &guiCoordSys) {
    guiCoordSys->AddChild(coordSys_);
}

void Button::UpdateRequiredSizes() {
    Vector<float> extents = textConsole_->BoundingBox().Extents();
    requiredSize_.width  = extents.x;
    requiredSize_.height = extents.y;
}

void Button::Layout(const Frame &frame) {
    frame_.position = frame.position;
    frame_.size     = requiredSize_;
    coordSys_->SetPosition(Vector<float>(frame_.position.x + .5f*frame_.size.width,
                                         frame_.position.y - .5f*frame_.size.height,
                                         0.0f));
    context_->redrawRequestHandler->OnRedrawRequested();
}

GuiElement *Button::TouchedElement(const TouchInfo &touch) {
    Log::Print(Log::Level::Debug, this, [&]{
        return "TouchedElement(), pos=(x=" + to_string(touch.x) + " ,y=" + to_string(touch.y) + ")";
    });
    return frame_.Contains(touch.x, touch.y) ? this : nullptr;
}

void Button::OnTouchGestureBegan(const vector<const TouchInfo *> &touches) {
    touchInside_ = true;
    SetBackgroundColor(true);
    context_->redrawRequestHandler->OnRedrawRequested();
}

void Button::OnTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    if (touches.size() == 1u) {
        touchInside_ = frame_.Contains(touches[0]->x, touches[0]->y);
        SetBackgroundColor(touchInside_);
        context_->redrawRequestHandler->OnRedrawRequested();
    }
}

void Button::OnTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    bool inside = touchInside_;
    
    touchInside_ = false;
    SetBackgroundColor(false);
    context_->redrawRequestHandler->OnRedrawRequested();
    
    if (inside) {
        puts("button clicked");
        // Activate handler.
    }
}

void Button::SetBackgroundColor(bool active) {
    if (active) {
        textConsole_->SetBackgroundColor(.35f * Vector<float>(.380f, .753f, .749f), 1.0f);
    } else {
        textConsole_->SetBackgroundColor(Vector<float>(1.0f, 1.0f, 1.0f), .125f);
    }
}
    
}    // Namespace Gui.
}    // Namespace Vectoid.
