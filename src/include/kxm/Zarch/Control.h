#ifndef KXM_ZARCH_CONTROL_H_
#define KXM_ZARCH_CONTROL_H_

#include <kxm/Core/NumberTools.h>

namespace kxm {
namespace Zarch {

enum ControlType { Axis1Control,
                   Axis2Control,
                   ThrusterControl,
                   PrimaryWeaponFiredControl };

//! Describes a certain type of control input to an actor.
/*!
 *  \ingroup Zarch
 *
 *  Such a control input has a type and a <c>float</c>-valued argument in the range <c>[-1, +1]</c>. The type implies
 *  whether a given control value has update or event semantics.
 */
class Control {
  public:
    Control(ControlType type)
            : type_(type),
              argument_(0.0f) {
        // Nop.
    }
    //! The argument will get clamped to the range <c>[-1, +1]</c>.
    Control(ControlType type, float argument)
            : type_(type),
              argument_(argument) {
        Core::NumberTools::Clamp(&argument_, -1.0f, 1.0f);
    }
        // Default copy/move ok.
    
    ControlType Type() const { return type_;     }
    float Argument() const   { return argument_; }
    
  private:
    ControlType type_;
    float       argument_;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_CONTROL_H_
