///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_GUI_FRAME_H_
#define VECTOID_GUI_FRAME_H_

#include <string>
#include <Vectoid/Gui/Position.h>
#include <Vectoid/Gui/Size.h>

namespace Vectoid {
namespace Gui {

//! Holds both position and size of an UI element.
struct Frame {
    Position position;
    Size     size;
    
    Frame(const Position &position, const Size &size) : position{position}, size{size} {}
    Frame()                              = default;
    Frame(const Frame &other)            = default;
    Frame &operator=(const Frame &other) = default;
    Frame(Frame &&other)                 = default;
    Frame &operator=(Frame &&other)      = default;
    ~Frame()                             = default;
    
    bool Contains(float x, float y) const {
        return (x >= position.x) && (x <= position.x + size.width)
                   && (y <= position.y) && (y >= position.y - size.height);
    }
    std::string ToString() const {
        return std::string("(position=") + position.ToString() + ", size=" + size.ToString() + ")";
    }
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_FRAME_H_
