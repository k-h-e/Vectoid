///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Gui/GuiElement.h>

#include <Vectoid/Gui/Context.h>

using std::shared_ptr;

namespace Vectoid {
namespace Gui {

GuiElement::GuiElement(const shared_ptr<Context> &context)
        : context_{context} {
    // Nop.
}

GuiElement::~GuiElement() {
    context_->Unregister(this);
}

void GuiElement::OnCyclicUpdate(float deltaTimeS) {
    // Nop.
}

}    // Namespace Gui.
}    // Namespace Vectoid.
