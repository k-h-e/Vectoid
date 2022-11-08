#ifndef VECTOID_GUI_TOUCHINFO_H_
#define VECTOID_GUI_TOUCHINFO_H_

namespace Vectoid {
namespace Gui {

//! Holds info on a touch.
struct TouchInfo {
    float x;
    float y;
    float startX;
    float startY;
    
    TouchInfo(float x, float y) : x(x), y(y), startX(x), startY(y) {}
    TouchInfo() : TouchInfo(0.0f, 0.0f) {}
    TouchInfo(const TouchInfo &other)            = default;
    TouchInfo &operator=(const TouchInfo &other) = default;
    TouchInfo(TouchInfo &&other)                 = default;
    TouchInfo &operator=(TouchInfo &&other)      = default;
    ~TouchInfo()                                 = default;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_TOUCHINFO_H_
