#include <Vectoid/Gui/GuiElement.h>

using std::shared_ptr;
using Vectoid::SceneGraph::RenderTargetInterface;

namespace Vectoid {
namespace Gui {

GuiElement::GuiElement(const shared_ptr<RenderTargetInterface> &renderTarget,
                       const shared_ptr<RedrawRequestHandlerInterface> &redrawRequestHandler) {
    // Nop.
}

}    // Namespace Gui.
}    // Namespace Vectoid.
