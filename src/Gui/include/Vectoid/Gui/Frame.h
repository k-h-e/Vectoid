#ifndef VECTOID_GUI_FRAME_H_
#define VECTOID_GUI_FRAME_H_

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
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_FRAME_H_
