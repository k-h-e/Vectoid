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

void Label::SetText(int row, const string &text, TextConsole::Color color) {
    textConsole_->ClearRow(row);
    textConsole_->WriteAt(0, row, text.c_str(), color);
    context_->RequestRedraw();
}

void Label::WriteLine(const string &line, TextConsole::Color color) {
    textConsole_->WriteLine(line, color);
    context_->RequestRedraw();
}

void Label::WriteAt(int column, int row, const string &text, TextConsole::Color color) {
    textConsole_->WriteAt(column, row, text.c_str(), color);
    context_->RequestRedraw();
}

void Label::ClearText() {
    textConsole_->Clear();
    context_->RequestRedraw();
}

void Label::ClearRow(int row) {
    textConsole_->ClearRow(row);
    context_->RequestRedraw();
}

void Label::AddSceneGraphNodes(CoordSys *guiCoordSys) {
    guiCoordSys->AddChild(coordSys_);
}

RequiredSize Label::UpdateRequiredSizes() {
    Vector<float> extents = textConsole_->BoundingBox().Extents();
    requiredSize_.size.width  = extents.x;
    requiredSize_.size.height = extents.y;
    return requiredSize_;
}

void Label::Layout(const Frame &frame) {
    if (horizontalAlignment_ == HorizontalAlignment::Right) {
        float x { frame.position.x + frame.size.width - requiredSize_.size.width };
        NumberTools::ClampMin(x, frame.position.x);
        frame_.position.x = x;
        frame_.position.y = frame.position.y;
    } else {
        frame_.position = frame.position;
    }
    frame_.size = requiredSize_.size;
    coordSys_->SetPosition(Vector<float>(frame_.position.x + .5f*frame_.size.width,
                                         frame_.position.y - .5f*frame_.size.height,
                                         0.0f));
    context_->RequestRedraw();
}

GuiElement *Label::TouchedElement(const TouchInfo &touch) {
    (void) touch;
    return nullptr;
}

void Label::OnTouchGestureBegan(const vector<const TouchInfo *> &touches) {
    (void) touches;
    // Nop.
}

void Label::OnTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    (void) touches;
    // Nop.
}

void Label::OnTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    (void) touches;
    // Nop.
}

}    // Namespace Gui.
}    // Namespace Vectoid.
