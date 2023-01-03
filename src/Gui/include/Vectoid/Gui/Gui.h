#ifndef VECTOID_GUI_GUI_H_
#define VECTOID_GUI_GUI_H_

#include <memory>
#include <optional>
#include <vector>
#include <K/Core/Interface.h>
#include <Vectoid/Gui/Frame.h>
#include <Vectoid/Gui/Types.h>

namespace Vectoid {
    namespace SceneGraph {
        class CoordSys;
        class RenderTargetInterface;
    }
    namespace Gui {
        class Button;
        class ComboBarrel;
        class CustomContentInterface;
        class Context;
        class CustomButton;
        class GuiElement;
        class RedrawRequestHandlerInterface;
        class Strip;
        struct TouchInfo;
    }
}

namespace Vectoid {
namespace Gui {

//! Graphical user interface.
class Gui : public virtual K::Core::Interface {
  public:
    //! Interface to GUI handlers.
    class HandlerInterface : public virtual K::Core::Interface {
      public:
        //! Informs the handler that the GUI requests a redraw.
        virtual void OnGuiRequestsRedraw() = 0;
        //! Informs the handler whether or not the GUI requests cyclic update calls.
        virtual void OnGuiRequestsCyclicUpdateCalls(bool requested) = 0;
    };
  
    Gui(const std::shared_ptr<SceneGraph::RenderTargetInterface> &renderTarget,
        const std::shared_ptr<SceneGraph::CoordSys> &coordSys);
    Gui()                            = delete;
    Gui(const Gui &other)            = delete;
    Gui &operator=(const Gui &other) = delete;
    Gui(Gui &&other)                 = delete;
    Gui &operator=(Gui &&other)      = delete;
    ~Gui()                           = default;
    
    //! Registers the specified handler.
    /*!
     *  Pass <c>nullptr</c> to unregister a previously registered handler. In that case, when the method returns it is
     *  guaranteed that the handler will not be called again.
     */
    void Register(HandlerInterface *handler);
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
    //! Tells whether the GUI is currently in the specified scene.
    bool InScene(int scene) const;
    //! Sets the GUI frame as specified.
    void SetFrame(const Frame &frame);
    //! Informs the GUI that a new frame is about to be rendered.
    void OnFrameWillBeRendered();
    //! Handles a cyclic update call (requested earlier).
    void OnCyclicUpdate(float deltaTimeS);
    //! Dispatches a touch gesture began event to the GUI and asks it to handle it.
    /*!
     *  \return <c>true</c> in case the GUI handled the touch gesture event.
     */
    bool HandleTouchGestureBegan(const std::vector<const TouchInfo *> &touches);
    //! Dispatches a touch gesture moved event to the GUI and asks it to handle it.
    /*!
     *  \return <c>true</c> in case the GUI handled the touch gesture event.
     */
    bool HandleTouchGestureMoved(const std::vector<const TouchInfo *> &touches);
    //! Dispatches a touch gesture ended event to the GUI and asks it to handle it.
    /*!
     *  \return <c>true</c> in case the GUI handled the touch gesture event.
     */
    bool HandleTouchGestureEnded(const std::vector<const TouchInfo *> &touches);
    //! Returns the global glyph size setting.
    Size GlyphSize() const;
    
    std::shared_ptr<Button> MakeButton(const std::string &text);
    std::shared_ptr<ComboBarrel> MakeComboBarrel(int width, int numVisibleOtherPerSide);
    //! Creates a new custom button.
    /*!
     *  \param width
     *  Custom button width in multiples of the GUI's glyph size.
     *
     *  \param height
     *  Custom button height in multiples of the GUI's glyph height.
     */
    std::shared_ptr<CustomButton> MakeCustomButton(const std::shared_ptr<CustomContentInterface> &content);
    std::shared_ptr<Strip> MakeStrip(Orientation orientation);

  private:
    void Layout();
    
    std::shared_ptr<SceneGraph::CoordSys>              coordSys_;
    Frame                                              frame_;
    std::vector<std::shared_ptr<GuiElement>>           scenes_;
    std::optional<int>                                 activeScene_;
    GuiElement                                         *activeElement_;
    std::shared_ptr<Context>                           context_;
    std::chrono::steady_clock::time_point              lastFrameTime_;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_GUI_H_
