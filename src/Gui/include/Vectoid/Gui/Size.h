///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_GUI_SIZE_H_
#define VECTOID_GUI_SIZE_H_

#include <string>

namespace Vectoid {
namespace Gui {

//! Holds the size of an UI element.
struct Size {
    float width;
    float height;
    
    Size(float width, float height) : width{width > 0.0f ? width : 0.0f}, height{height > 0.0f ? height : 0.0f} {}
    Size() : width{0.0f}, height{0.0f} {}
    Size(const Size &other)            = default;
    Size &operator=(const Size &other) = default;
    Size(Size &&other)                 = default;
    Size &operator=(Size &&other)      = default;
    ~Size()                            = default;
    
    void EnsurePositive() {
        width  = (width > 0.0f) ? width : 1.0f;
        height = (height > 0.0f) ? height : 1.0f;
    }
    std::string ToString() const {
        return std::string("(width=") + std::to_string(width) + ", height=" + std::to_string(height) + ")";
    }
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_SIZE_H_
