///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Gui/Label.h>

#include <K/Core/StringTools.h>
#include <Vectoid/Gui/Context.h>
#include <Vectoid/Gui/TouchInfo.h>
#include <Vectoid/SceneGraph/CoordSys.h>
#include <Vectoid/SceneGraph/Geode.h>
#include <Vectoid/SceneGraph/RenderTargetInterface.h>
#include <Vectoid/SceneGraph/TextConsole.h>

using std::shared_ptr;
using std::string;
using std::vector;
using K::Core::StringTools;
using Vectoid::Core::Vector;
using Vectoid::SceneGraph::CoordSys;
using Vectoid::SceneGraph::TextConsole;

namespace Vectoid {
namespace Gui {

Label::Label(const string &text, const Size &glyphSize, const shared_ptr<Context> &context)
        : GuiElement{context} {
    int width = static_cast<int>(text.length());
    width     = (width > 0) ? width : 1;
    Construct(width, 1, glyphSize);
    textConsole_->WriteAt(0, 0, text.c_str(), TextConsole::Color::White);
}

Label::Label(int width, int height, const Size &glyphSize, const shared_ptr<Context> &context)
        : GuiElement{context} {
    width  = (width > 0) ? width : 1;
    height = (height > 0) ? height : 1;
    Construct(width, height, glyphSize);
}

void Label::Construct(int width, int height, const Size &glyphSize) {
    auto size = glyphSize;
    size.EnsurePositive();
    textConsole_ = context_->renderTarget->NewTextConsole(width, height, size.width, size.height, context_->glyphs);
    textConsole_->SetCustomColor(context_->menuTextColor);
    textConsole_->SetBackgroundColor(context_->labelBackgroundColor, context_->labelBackgroundAlpha);
    coordSys_    = context_->renderTarget->NewCoordSys();
    coordSys_->AddChild(context_->renderTarget->NewGeode(textConsole_));
}

void Label::SetText(const string &text) {
    SetText(0, text, TextConsole::Color::White);
}

void Label::SetText(int line, const string &text, TextConsole::Color color) {
    textConsole_->ClearRow(line);
    textConsole_->WriteAt(0, line, text.c_str(), color);
    context_->RequestRedraw();
}

void Label::WriteLine(const string &line, TextConsole::Color color) {
    textConsole_->WriteLine(line, color);
    context_->RequestRedraw();
}

void Label::ClearText() {
    textConsole_->Clear();
    context_->RequestRedraw();
}

void Label::AddSceneGraphNodes(CoordSys *guiCoordSys) {
    guiCoordSys->AddChild(coordSys_);
}

Size Label::UpdateRequiredSizes() {
    Vector<float> extents = textConsole_->BoundingBox().Extents();
    requiredSize_.width  = extents.x;
    requiredSize_.height = extents.y;
    return requiredSize_;
}

void Label::Layout(const Frame &frame) {
    frame_.position = frame.position;
    frame_.size     = requiredSize_;
    coordSys_->SetPosition(Vector<float>(frame_.position.x + .5f*frame_.size.width,
                                         frame_.position.y - .5f*frame_.size.height,
                                         0.0f));
    context_->RequestRedraw();
}

GuiElement *Label::TouchedElement(const TouchInfo &touch) {
    return nullptr;
}

void Label::OnTouchGestureBegan(const vector<const TouchInfo *> &touches) {
    // Nop.
}

void Label::OnTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    // Nop.
}

void Label::OnTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    // Nop.
}

}    // Namespace Gui.
}    // Namespace Vectoid.
