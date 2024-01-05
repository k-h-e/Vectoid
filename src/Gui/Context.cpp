///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Gui/Context.h>

#include <K/Core/Log.h>
#include <Vectoid/Gui/GuiElement.h>

using std::shared_ptr;
using std::to_string;
using K::Core::Log;
using Vectoid::SceneGraph::Glyphs;
using Vectoid::SceneGraph::RenderTargetInterface;

namespace Vectoid {
namespace Gui {

Context::Context(const shared_ptr<RenderTargetInterface> &renderTarget, const shared_ptr<Glyphs> &glyphs, float scale)
        : renderTarget { renderTarget },
          glyphs { glyphs },
          glyphSize { ValidateScale(scale) * .018f, ValidateScale(scale) * .03f },
          frameWidth { ValidateScale(scale) * .0025f },
          spacing { ValidateScale(scale) * .02f },
          labelBackgroundColor { 0.0f, 0.0f, 0.0f },
          labelBackgroundAlpha { .65f },
          menuBackgroundColor { 0.0f, 0.0f, 0.0f },
          menuBackgroundAlpha { .65f },
          menuTextColor { .380f, .753f, .749f },
          selectionTextColor { 1.0f, 1.0f, 1.0f },
          selectionBackgroundColor { .35f * menuTextColor },
          handler_ { nullptr },
          layoutRequired_ { false } {
    // Nop.
}

void Context::SetHandler(Gui::HandlerInterface *handler) {
    handler_ = handler;
    cyclicUpdateCallsRequested_.reset();
    RequestRedraw();
    UpdateCyclicUpdateCallsRequest();
}

void Context::Unregister(GuiElement *element) {
    elementsNeedingCyclicUpdateCalls_.erase(element);
    UpdateCyclicUpdateCallsRequest();
}

void Context::SetLayoutRequired(bool required) {
    layoutRequired_ = required;
}

bool Context::LayoutRequired() const {
    return layoutRequired_;
}

void Context::RequestRedraw() {
    if (handler_) {
        handler_->OnGuiRequestsRedraw();
    }
}

void Context::RequestCyclicUpdateCalls(GuiElement *element, bool requested) {
    if (requested) {
        elementsNeedingCyclicUpdateCalls_.insert(element);
    } else {
        elementsNeedingCyclicUpdateCalls_.erase(element);
    }
    Log::Print(Log::Level::Debug, this, [&]{
        return to_string(elementsNeedingCyclicUpdateCalls_.size()) + " GUI elements have requested cyclic updates";
    });
    UpdateCyclicUpdateCallsRequest();
}

void Context::OnCyclicUpdate(float deltaTimeS) {
    for (GuiElement *element : elementsNeedingCyclicUpdateCalls_) {
        element->OnCyclicUpdate(deltaTimeS);
    }
}

void Context::UpdateCyclicUpdateCallsRequest() {
    bool cyclicUpdateCallsRequired = !elementsNeedingCyclicUpdateCalls_.empty();
    if (!cyclicUpdateCallsRequested_ || (cyclicUpdateCallsRequired != *cyclicUpdateCallsRequested_)) {
        cyclicUpdateCallsRequested_ = cyclicUpdateCallsRequired;
        if (handler_) {
            if (*cyclicUpdateCallsRequested_) {
                Log::Print(Log::Level::Debug, this, [&]{ return "enabling cyclic GUI updates"; });
            } else {
                Log::Print(Log::Level::Debug, this, [&]{ return "disbling cyclic GUI updates"; });
            }
            handler_->OnGuiRequestsCyclicUpdateCalls(*cyclicUpdateCallsRequested_);
        }
    }
}

float Context::ValidateScale(float scale) {
    return (scale > 0.0f) ? scale : 1.0f;
}

}    // Namespace Gui.
}    // Namespace Vectoid.
