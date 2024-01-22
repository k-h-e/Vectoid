///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_GUI_REQUIREDSIZE_H_
#define VECTOID_GUI_REQUIREDSIZE_H_

#include <Vectoid/Gui/Size.h>

namespace Vectoid {
namespace Gui {

//! Holds the required size of an UI element.
struct RequiredSize {
    Size size;
    bool canUseMoreWidth;
    bool canUseMoreHeight;
    
    RequiredSize() : canUseMoreWidth{false}, canUseMoreHeight{false} {}
    RequiredSize(const RequiredSize &other)            = default;
    RequiredSize &operator=(const RequiredSize &other) = default;
    RequiredSize(RequiredSize &&other)                 = default;
    RequiredSize &operator=(RequiredSize &&other)      = default;
    ~RequiredSize()                                    = default;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_REQUIREDSIZE_H_
