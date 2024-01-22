///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

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
        class EmptySpace;
        class GuiElement;
        class Label;
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
        const std::shared_ptr<SceneGraph::CoordSys> &coordSys, float scale);
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
    //! Tells the scene the GUI is currently in.
    std::optional<int> CurrentScene() const;
    //! Tells whether the GUI is currently in the specified scene.
    bool InScene(int scene) const;
    //! Sets the GUI frame as specified.
    void SetFrame(const Frame &frame, bool addMargin);
    //! Informs the GUI that a new frame is about to be rendered.
    void OnFrameWillBeRendered();
    //! Handles a cyclic update call (requested earlier).
    void OnCyclicUpdate(float deltaTimeS);
    //! Dispatches a touch gesture began event to the GUI and asks it whether it will handle the gesture.
    /*!
     *  \return <c>true</c> in case the GUI will handle the touch gesture.
     */
    bool OnTouchGestureBegan(const std::vector<const TouchInfo *> &touches);
    //! Dispatches a touch gesture moved event to the GUI.
    void OnTouchGestureMoved(const std::vector<const TouchInfo *> &touches);
    //! Dispatches a touch gesture ended event to the GUI.
    void OnTouchGestureEnded(const std::vector<const TouchInfo *> &touches);
    //! Returns the global glyph size setting.
    Size GlyphSize() const;
    
    std::shared_ptr<Button> MakeButton(const std::string &text);
    std::shared_ptr<ComboBarrel> MakeComboBarrel(int width, int numVisibleOtherPerSide);
    std::shared_ptr<CustomButton> MakeCustomButton(const std::shared_ptr<CustomContentInterface> &content);
    std::shared_ptr<EmptySpace> MakeEmptySpace(bool extendsHorizontally, bool extendsVertically);
    std::shared_ptr<Label> MakeLabel(const std::string &text);
    std::shared_ptr<Label> MakeLabel(int width, int height);
    std::shared_ptr<Strip> MakeStrip(Orientation orientation);

  private:
    void Layout();
    
    std::shared_ptr<Context>                           context_;
    std::shared_ptr<SceneGraph::CoordSys>              coordSys_;
    Frame                                              frame_;
    std::vector<std::shared_ptr<GuiElement>>           scenes_;
    std::optional<int>                                 currentScene_;
    bool                                               touchGestureOngoing_;
    int                                                gestureNumTouches_;
    GuiElement                                         *touchGestureElement_;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_GUI_H_
