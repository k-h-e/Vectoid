#include <Vectoid/Gui/Gui.h>

#include <Vectoid/Gui/Button.h>
#include <Vectoid/Gui/ComboBarrel.h>
#include <Vectoid/Gui/Context.h>
#include <Vectoid/Gui/TouchInfo.h>
#include <Vectoid/Gui/RedrawRequestHandlerInterface.h>
#include <Vectoid/SceneGraph/CoordSys.h>
#include <Vectoid/SceneGraph/Glyphs.h>
#include <Vectoid/SceneGraph/RenderTargetInterface.h>

using std::shared_ptr;
using std::string;
using std::vector;
using Vectoid::SceneGraph::CoordSys;
using Vectoid::SceneGraph::Glyphs;
using Vectoid::SceneGraph::RenderTargetInterface;
using Vectoid::Gui::RedrawRequestHandlerInterface;

namespace Vectoid {
namespace Gui {

Gui::Gui(const shared_ptr<RenderTargetInterface> &renderTarget, const shared_ptr<CoordSys> &coordSys,
         const shared_ptr<RedrawRequestHandlerInterface> &redrawRequestHandler)
        : coordSys_{coordSys},
          activeElement_{nullptr} {
    auto glyphs = renderTarget->NewGlyphs();
    context_ = make_shared<Context>(renderTarget, glyphs, redrawRequestHandler);
}

int Gui::AddScene(const shared_ptr<GuiElement> &root) {
    int id = static_cast<int>(scenes_.size());
    scenes_.push_back(root);
    return id;
}

void Gui::EnterScene(int scene) {
    if ((scene >= 0) && (scene < static_cast<int>(scenes_.size()))) {
        coordSys_->RemoveAllChildren();
        auto &sceneRoot = scenes_[scene];
        sceneRoot->AddSceneGraphNodes(coordSys_);
        activeScene_ = scene;
        Layout();
    }
}

void Gui::SetFrame(const Frame &frame) {
    frame_ = frame;
    Layout();
}

bool Gui::HandleTouchGestureBegan(const vector<const TouchInfo *> &touches) {
    puts("Gui::HandleTouchGestureBegan()");
    if (activeScene_) {
        auto &sceneRoot = scenes_[*activeScene_];
        if (touches.size() == 1u) {
            activeElement_ = sceneRoot->TouchedElement(*(touches[0]));
            if (activeElement_) {
                activeElement_->OnTouchGestureBegan(touches);
                return true;
            }
        }
    }
    
    activeElement_ = nullptr;
    return false;
}

bool Gui::HandleTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    if (activeElement_) {
        activeElement_->OnTouchGestureMoved(touches);
        return true;
    } else {
        return false;
    }
}

bool Gui::HandleTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    if (activeElement_) {
        activeElement_->OnTouchGestureEnded(touches);
        activeElement_ = nullptr;
        return true;
    } else {
        return false;
    }
}

shared_ptr<ComboBarrel> Gui::NewComboBarrel(int width, int numVisibleOtherPerSide, float glyphWidth,
                                            float glyphHeight) {
    return shared_ptr<ComboBarrel>(new ComboBarrel(width, numVisibleOtherPerSide, glyphWidth, glyphHeight, context_));
}

shared_ptr<Button> Gui::NewButton(const string &text, float glyphWidth, float glyphHeight) {
    return shared_ptr<Button>(new Button(text, glyphWidth, glyphHeight, context_));
}

void Gui::Layout() {
    if (activeScene_) {
        auto &sceneRoot = scenes_[*activeScene_];
        sceneRoot->UpdateRequiredSizes();
        sceneRoot->Layout(frame_);
        context_->redrawRequestHandler->OnRedrawRequested();
    }
}

}    // Namespace Gui.
}    // Namespace Vectoid.
