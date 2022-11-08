#include <Vectoid/Gui/GuiElement.h>

using std::shared_ptr;

namespace Vectoid {
namespace Gui {

GuiElement::GuiElement(const shared_ptr<Context> &context)
        : context_{context} {
    // Nop.
}

}    // Namespace Gui.
}    // Namespace Vectoid.
