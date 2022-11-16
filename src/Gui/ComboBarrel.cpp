#include <Vectoid/Gui/ComboBarrel.h>

#include <Vectoid/Gui/Context.h>
#include <Vectoid/Gui/RedrawRequestHandlerInterface.h>
#include <Vectoid/Gui/TouchInfo.h>
#include <Vectoid/SceneGraph/ComboBarrel.h>
#include <Vectoid/SceneGraph/CoordSys.h>
#include <Vectoid/SceneGraph/Geode.h>
#include <Vectoid/SceneGraph/RenderTargetInterface.h>

using std::make_shared;
using std::shared_ptr;
using std::string;
using std::vector;
using Vectoid::Core::Vector;
using Vectoid::Gui::TouchInfo;
using Vectoid::SceneGraph::CoordSys;

namespace Vectoid {
namespace Gui {

struct TouchInfo;

ComboBarrel::ComboBarrel(int width, int numVisibleOtherPerSide, float glyphWidth, float glyphHeight,
                         const shared_ptr<Context> &context)
        : GuiElement{context},
          startPosition_{0.0f} {
    comboBarrel_ = context_->renderTarget->NewComboBarrel(width, numVisibleOtherPerSide, glyphWidth, glyphHeight,
                                                          context_->glyphs);
    coordSys_    = context_->renderTarget->NewCoordSys();
    coordSys_->AddChild(context_->renderTarget->NewGeode(comboBarrel_));
              
    SetBackgroundColor(false);
}

void ComboBarrel::Clear() {
    comboBarrel_->Clear();
}

int ComboBarrel::AddItem(const string &item) {
    return comboBarrel_->AddItem(item);
}

void ComboBarrel::AddSceneGraphNodes(const shared_ptr<CoordSys> &guiCoordSys) {
    guiCoordSys->AddChild(coordSys_);
}

void ComboBarrel::UpdateRequiredSizes() {
    Vector<float> extents = comboBarrel_->BoundingBox().Extents();
    requiredSize_.width  = extents.x;
    requiredSize_.height = extents.y;
}

void ComboBarrel::Layout(const Frame &frame) {
    frame_.position = frame.position;
    frame_.size     = requiredSize_;
    coordSys_->SetPosition(Vector<float>(frame_.position.x + .5f*frame_.size.width,
                                         frame_.position.y - .5f*frame_.size.height,
                                         0.0f));
    context_->redrawRequestHandler->OnRedrawRequested();
}

GuiElement *ComboBarrel::TouchedElement(const TouchInfo &touch) {
    return frame_.Contains(touch.x, touch.y) ? this : nullptr;
}

void ComboBarrel::OnTouchGestureBegan(const vector<const TouchInfo *> &touches) {
    startPosition_ = comboBarrel_->Position();
    SetBackgroundColor(true);
    context_->redrawRequestHandler->OnRedrawRequested();
}

void ComboBarrel::OnTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    if (touches.size() == 1u) {
        const TouchInfo &touch = *(touches[0]);
        float t = (touch.y - touch.startY) / frame_.size.height;
        comboBarrel_->SetPosition(startPosition_ + t*8.0f);
        context_->redrawRequestHandler->OnRedrawRequested();
    }
}

void ComboBarrel::OnTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    SetBackgroundColor(false);
    context_->redrawRequestHandler->OnRedrawRequested();
}

void ComboBarrel::SetBackgroundColor(bool active) {
    if (active) {
        comboBarrel_->SetBackgroundColor(.35f * Vector<float>(.380f, .753f, .749f), 1.0f);
    } else {
        comboBarrel_->SetBackgroundColor(Vector<float>(1.0f, 1.0f, 1.0f), .125f);
    }
}

}    // Namespace Gui.
}    // Namespace Vectoid.
