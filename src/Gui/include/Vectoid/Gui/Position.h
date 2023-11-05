///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_GUI_POSITION_H_
#define VECTOID_GUI_POSITION_H_

namespace Vectoid {
namespace Gui {

//! Holds the position of an UI element (i.e. its upper-left corner).
struct Position {
    float x;
    float y;
    
    Position(float x, float y) : x{x}, y{y} {}
    Position() : x{0.0f}, y{0.0f} {}
    Position(const Position &other)            = default;
    Position &operator=(const Position &other) = default;
    Position(Position &&other)                 = default;
    Position &operator=(Position &&other)      = default;
    ~Position()                                = default;
    
    std::string ToString() const {
        return std::string("(x=") + std::to_string(x) + ", y=" + std::to_string(y) + ")";
    }
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_POSITION_H_
