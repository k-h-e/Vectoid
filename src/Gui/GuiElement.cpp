///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Gui/GuiElement.h>

#include <Vectoid/Gui/Context.h>

using std::shared_ptr;

namespace Vectoid {
namespace Gui {

GuiElement::GuiElement(const shared_ptr<Context> &context)
        : horizontalAlignment_{HorizontalAlignment::Left},
          verticalAlignment_{VerticalAlignment::Top},
          context_{context} {
    // Nop.
}

GuiElement::~GuiElement() {
    context_->Unregister(this);
}

void GuiElement::SetHorizontalAlignment(HorizontalAlignment alignment) {
    horizontalAlignment_ = alignment;
    context_->SetLayoutRequired(true);
}

void GuiElement::SetVerticalAlignment(VerticalAlignment alignment) {
    verticalAlignment_ = alignment;
    context_->SetLayoutRequired(true);
}

void GuiElement::OnCyclicUpdate(float deltaTimeS) {
    (void) deltaTimeS;
    // Nop.
}

}    // Namespace Gui.
}    // Namespace Vectoid.
