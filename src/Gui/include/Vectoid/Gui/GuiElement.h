#ifndef VECTOID_GUI_GUIELEMENT_H_
#define VECTOID_GUI_GUIELEMENT_H_

#include <memory>
#include <K/Core/Interface.h>
#include <Vectoid/Gui/Position.h>
#include <Vectoid/Gui/Size.h>

namespace Vectoid {
    namespace SceneGraph {
        class CoordSys;
        class RenderTargetInterface;
    }
    namespace Gui {
        struct Frame;
        class RedrawRequestHandlerInterface;
    }
}

namespace Vectoid {
namespace Gui {

//! Base class to Vectoid graphical user interface elements.
class GuiElement : public virtual K::Core::Interface {
  public:
    GuiElement(const std::shared_ptr<SceneGraph::RenderTargetInterface> &renderTarget,
               const std::shared_ptr<RedrawRequestHandlerInterface> &redrawRequestHandler);
    GuiElement()                                   = delete;
    GuiElement(const GuiElement &other)            = delete;
    GuiElement &operator=(const GuiElement &other) = delete;
    GuiElement(GuiElement &&other)                 = delete;
    GuiElement &operator=(GuiElement &&other)      = delete;
    ~GuiElement()                                  = default;
    //! Recursively adds scene graph nodes to the specified GUI coordinate system that represent this GUI element and its children.
    virtual void AddSceneGraphNodes(const std::shared_ptr<SceneGraph::CoordSys> &guiCoordSys) = 0;
    //! Recursively updates the sizes of this GUI element and its children.
    virtual void UpdateSizes() = 0;
    //! Recursively updates the positions of this GUI element and its children.
    virtual void UpdatePositions(const Frame &frame) = 0;
    
  private:
    Position position_;
    Size     size_;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_GUIELEMENT_H_
