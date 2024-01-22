///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Gui/Gui.h>

#include <K/Core/Log.h>
#include <Vectoid/Gui/Button.h>
#include <Vectoid/Gui/ComboBarrel.h>
#include <Vectoid/Gui/Context.h>
#include <Vectoid/Gui/CustomButton.h>
#include <Vectoid/Gui/EmptySpace.h>
#include <Vectoid/Gui/Label.h>
#include <Vectoid/Gui/TouchInfo.h>
#include <Vectoid/Gui/Strip.h>
#include <Vectoid/SceneGraph/CoordSys.h>
#include <Vectoid/SceneGraph/Glyphs.h>
#include <Vectoid/SceneGraph/RenderTargetInterface.h>

using std::optional;
using std::shared_ptr;
using std::string;
using std::to_string;
using std::vector;
using K::Core::Log;
using Vectoid::SceneGraph::CoordSys;
using Vectoid::SceneGraph::Glyphs;
using Vectoid::SceneGraph::RenderTargetInterface;
using Vectoid::Gui::RedrawRequestHandlerInterface;

namespace Vectoid {
namespace Gui {

Gui::Gui(const shared_ptr<RenderTargetInterface> &renderTarget, const shared_ptr<CoordSys> &coordSys, float scale)
        : coordSys_{coordSys},
          touchGestureOngoing_{false},
          gestureNumTouches_{0},
          touchGestureElement_{nullptr} {
    auto glyphs = renderTarget->NewGlyphs();
    context_ = make_shared<Context>(renderTarget, glyphs, scale);
}

void Gui::Register(HandlerInterface *handler) {
    context_->SetHandler(handler);
}

int Gui::AddScene(const shared_ptr<GuiElement> &root) {
    int id = static_cast<int>(scenes_.size());
    scenes_.push_back(root);
    return id;
}

void Gui::EnterScene(int scene) {
    if ((scene >= 0) && (scene < static_cast<int>(scenes_.size()))) {
        Log::Print(Log::Level::Debug, this, [&]{ return "entering scene " + to_string(*currentScene_); });
        coordSys_->RemoveAllChildren();
        auto &sceneRoot = scenes_[scene];
        sceneRoot->AddSceneGraphNodes(coordSys_.get());
        currentScene_ = scene;
        Layout();
    }
}

optional<int> Gui::CurrentScene() const {
    return currentScene_;
}

bool Gui::InScene(int scene) const {
    return (currentScene_ && (*currentScene_ == scene));
}

void Gui::SetFrame(const Frame &frame, bool addMargin) {
    frame_ = frame;
    if (addMargin) {
        if ((frame_.size.width > 2.0f * context_->spacing) && (frame_.size.height > 2.0f * context_->spacing)) {
            frame_.position.x  += context_->spacing;
            frame_.position.y  -= context_->spacing;
            frame_.size.width  -= 2.0f * context_->spacing;
            frame_.size.height -= 2.0f * context_->spacing;
        }
    }
    Layout();
}

void Gui::OnFrameWillBeRendered() {    
    if (context_->LayoutRequired()) {
        context_->SetLayoutRequired(false);
        Layout();
    }
}

void Gui::OnCyclicUpdate(float deltaTimeS) {
    context_->OnCyclicUpdate(deltaTimeS);
}

bool Gui::OnTouchGestureBegan(const vector<const TouchInfo *> &touches) {
    if (!touchGestureOngoing_) {
        int numTouches = static_cast<int>(touches.size());
        if (numTouches == 1) {
            if (currentScene_) {
                auto &sceneRoot = scenes_[*currentScene_];
                touchGestureElement_ = sceneRoot->TouchedElement(*(touches[0]));
                if (touchGestureElement_) {
                    touchGestureOngoing_ = true;
                    gestureNumTouches_   = numTouches;
                    touchGestureElement_->OnTouchGestureBegan(touches);
                    return true;
                }
            }
        }
    } else {
        Log::Print(Log::Level::Error, this, [&]{ return "ignoring bad OnTouchGestureBegan() call!"; });
    }
    
    return false;
}

void Gui::OnTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    if (touchGestureOngoing_ && (static_cast<int>(touches.size()) == gestureNumTouches_)) {
        if (touchGestureElement_) {
            touchGestureElement_->OnTouchGestureMoved(touches);
        }
    } else {
      Log::Print(Log::Level::Error, this, [&]{ return "ignoring bad OnTouchGestureMoved() call!"; });
    }
}

void Gui::OnTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    if (touchGestureOngoing_ && (static_cast<int>(touches.size()) == gestureNumTouches_)) {
        GuiElement *element = touchGestureElement_;
        touchGestureOngoing_ = false;
        gestureNumTouches_   = 0;
        touchGestureElement_ = nullptr;
        if (element) {
            element->OnTouchGestureEnded(touches);
        }
    } else {
      Log::Print(Log::Level::Error, this, [&]{ return "ignoring bad OnTouchGestureEnded() call!"; });
    }
}

Size Gui::GlyphSize() const {
    return context_->glyphSize;
}

shared_ptr<Button> Gui::MakeButton(const string &text) {
    return shared_ptr<Button>{new Button{text, context_->glyphSize, context_}};
}

shared_ptr<ComboBarrel> Gui::MakeComboBarrel(int width, int numVisibleOtherPerSide) {
    return shared_ptr<ComboBarrel>{new ComboBarrel{width, numVisibleOtherPerSide, context_->glyphSize, context_}};
}

shared_ptr<CustomButton> Gui::MakeCustomButton(const shared_ptr<CustomContentInterface> &content) {
    return shared_ptr<CustomButton>{new CustomButton{content, context_}};
}

shared_ptr<EmptySpace> Gui::MakeEmptySpace(bool extendsHorizontally, bool extendsVertically) {
    return shared_ptr<EmptySpace>{new EmptySpace{extendsHorizontally, extendsVertically, context_}};
}

shared_ptr<Label> Gui::MakeLabel(const string &text) {
    return shared_ptr<Label>{new Label{text, context_->glyphSize, context_}};
}

shared_ptr<Label> Gui::MakeLabel(int width, int height) {
    return shared_ptr<Label>{new Label{width, height, context_->glyphSize, context_}};
}

shared_ptr<Strip> Gui::MakeStrip(Orientation orientation) {
    return shared_ptr<Strip>{new Strip{orientation, context_}};
}

void Gui::Layout() {
    if (currentScene_) {
        Log::Print(Log::Level::Debug, this, [&]{ return "updating layout"; });
        auto &sceneRoot = scenes_[*currentScene_];
        sceneRoot->UpdateRequiredSizes();
        sceneRoot->Layout(frame_);
        context_->RequestRedraw();
    }
}

}    // Namespace Gui.
}    // Namespace Vectoid.
