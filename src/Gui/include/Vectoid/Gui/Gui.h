#ifndef VECTOID_GUI_GUI_H_
#define VECTOID_GUI_GUI_H_

#include <memory>
#include <vector>
#include <K/Core/Interface.h>
#include <Vectoid/Gui/Frame.h>

namespace Vectoid {
    namespace SceneGraph {
        class CoordSys;
        class RenderTargetInterface;
    }
    namespace Gui {
        class GuiElement;
        class RedrawRequestHandlerInterface;
    }
}

namespace Vectoid {
namespace Gui {

//! Graphical user interface.
class Gui : public virtual K::Core::Interface {
  public:
    Gui(const std::shared_ptr<SceneGraph::RenderTargetInterface> &renderTarget,
        const std::shared_ptr<SceneGraph::CoordSys> &coordSys, const Frame &frame,
        const std::shared_ptr<RedrawRequestHandlerInterface> &redrawRequestHandler);
    Gui()                            = delete;
    Gui(const Gui &other)            = delete;
    Gui &operator=(const Gui &other) = delete;
    Gui(Gui &&other)                 = delete;
    Gui &operator=(Gui &&other)      = delete;
    ~Gui()                           = default;
    //! Adds the specified scene.
    /*!
     *  \param root
     *  Root GUI element of the scene to add.
     *
     *  \return Scene ID.
     */
    int AddScene(const std::shared_ptr<GuiElement> &root);
    //! Makes the GUI enter the specified scene.
    void EnterScene(int scene);

  private:
    std::shared_ptr<SceneGraph::RenderTargetInterface> renderTarget_;
    std::shared_ptr<SceneGraph::CoordSys>              coordSys_;
    Frame                                              frame_;
    std::shared_ptr<RedrawRequestHandlerInterface>     redrawRequestHandler_;
    std::vector<std::shared_ptr<GuiElement>>           scenes_;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_GUI_H_
