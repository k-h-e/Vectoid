///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_GUI_GUIELEMENT_H_
#define VECTOID_GUI_GUIELEMENT_H_

#include <memory>
#include <vector>

#include <K/Core/Interface.h>
#include <Vectoid/Gui/Frame.h>
#include <Vectoid/Gui/RequiredSize.h>

namespace Vectoid {
    namespace SceneGraph {
        class CoordSys;
    }
    namespace Gui {
        class Context;
        class RedrawRequestHandlerInterface;
        struct TouchInfo;
    }
}

namespace Vectoid {
namespace Gui {

//! Base class to Vectoid graphical user interface elements.
class GuiElement : public virtual K::Core::Interface {
  public:
    enum class HorizontalAlignment { Left,
                                     Center,
                                     Right   };
    enum class VerticalAlignment { Top,
                                   Center,
                                   Bottom  };

    GuiElement(const std::shared_ptr<Context> &context);
    GuiElement()                                   = delete;
    GuiElement(const GuiElement &other)            = delete;
    GuiElement &operator=(const GuiElement &other) = delete;
    GuiElement(GuiElement &&other)                 = delete;
    GuiElement &operator=(GuiElement &&other)      = delete;
    ~GuiElement();
    
    //! Sets the UI element's horizontal alignment.
    void SetHorizontalAlignment(HorizontalAlignment alignment);
    //! Sets the UI element's vertical alignment.
    void SetVerticalAlignment(VerticalAlignment alignment);

    //! Recursively adds to the specified GUI coordinate system scene graph nodes that represent this GUI element and
    //! its children.
    virtual void AddSceneGraphNodes(SceneGraph::CoordSys *guiCoordSys) = 0;
    //! Recursively updates the required sizes of this GUI element and its children.
    /*!
     *  \return Required size of the GUI element.
     */
    virtual RequiredSize UpdateRequiredSizes() = 0;
    //! Recursively layouts this GUI element and its children into the specified available frame.
    virtual void Layout(const Frame &frame) = 0;
    //! Handles a cyclic update call (requested earlier).
    virtual void OnCyclicUpdate(float deltaTimeS);
    //! Tells which GUI element in the subtree was touched by the specified touch.
    /*!
     *  \return <c>nullptr</c> in case no GUI element was touched.
     */
    virtual GuiElement *TouchedElement(const TouchInfo &touch) = 0;
    //! Dispatches a touch gesture began event to the GUI element.
    virtual void OnTouchGestureBegan(const std::vector<const TouchInfo *> &touches) = 0;
    //! Dispatches a touch gesture moved event to the GUI element.
    virtual void OnTouchGestureMoved(const std::vector<const TouchInfo *> &touches) = 0;
    //! Dispatches a touch gesture ended event to the GUI element.
    virtual void OnTouchGestureEnded(const std::vector<const TouchInfo *> &touches) = 0;
    
  protected:
    Frame                    frame_;
    RequiredSize             requiredSize_;
    HorizontalAlignment      horizontalAlignment_;
    VerticalAlignment        verticalAlignment_;
    std::shared_ptr<Context> context_;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_GUIELEMENT_H_
