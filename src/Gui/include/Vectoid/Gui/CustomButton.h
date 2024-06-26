///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_GUI_CUSTOMBUTTON_H_
#define VECTOID_GUI_CUSTOMBUTTON_H_

#include <optional>

#include <Vectoid/Core/Vector.h>
#include <Vectoid/Gui/GuiElement.h>

namespace Vectoid {
    namespace Gui {
        class Gui;
        struct TouchInfo;
    }
    namespace SceneGraph {
        class CustomPanel;
    }
}

namespace Vectoid {
namespace Gui {

class CustomContentInterface;

//! Custom button GUI element.
class CustomButton : public GuiElement {
  public:
    class HandlerInterface : public virtual K::Core::Interface {
      public:
        virtual void OnCustomButtonPressed(CustomButton *button) = 0;
    };
    
    friend class Gui;
    
    CustomButton()                                     = delete;
    CustomButton(const CustomButton &other)            = delete;
    CustomButton &operator=(const CustomButton &other) = delete;
    CustomButton(CustomButton &&other)                 = delete;
    CustomButton &operator=(CustomButton &&other)      = delete;
    ~CustomButton()                                    = default;
    
    //! Pass <c>nullptr</c> to unregister a potentially registered handler.
    void Register(HandlerInterface *handler);
    //! Toggles content animation.
    void EnableAnimation(bool enabled);
    //! Sets the specified custom colors.
    void SetCustomColors(const Core::Vector<float> &foregroundColor,
                         const Core::Vector<float> &backgroundColor);
    //! Clears custom colors if any are set.
    void ClearCustomColors();
    
    void AddSceneGraphNodes(SceneGraph::CoordSys *guiCoordSys) override;
    RequiredSize UpdateRequiredSizes() override;
    void Layout(const Frame &frame) override;
    void OnCyclicUpdate(float deltaTimeS) override;
    GuiElement *TouchedElement(const TouchInfo &touch) override;
    void OnTouchGestureBegan(const std::vector<const TouchInfo *> &touches) override;
    void OnTouchGestureMoved(const std::vector<const TouchInfo *> &touches) override;
    void OnTouchGestureEnded(const std::vector<const TouchInfo *> &touches) override;
    
  private:
    CustomButton(const std::shared_ptr<CustomContentInterface> &content, const std::shared_ptr<Context> &context);
    void SetColors();
    
    HandlerInterface                         *handler_;
    std::shared_ptr<CustomContentInterface>  content_;
    std::shared_ptr<SceneGraph::CustomPanel> panel_;
    std::shared_ptr<SceneGraph::CoordSys>    coordSys_;
    bool                                     touchInside_;
    bool                                     animationEnabled_;
    std::optional<Core::Vector<float>>       foregroundColor_;
    std::optional<Core::Vector<float>>       backgroundColor_;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_CUSTOMBUTTON_H_
