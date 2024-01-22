///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_GUI_STRIP_H_
#define VECTOID_GUI_STRIP_H_

#include <memory>
#include <vector>
#include <Vectoid/Gui/GuiElement.h>
#include <Vectoid/Gui/Types.h>

namespace Vectoid {
    namespace Gui {
        class Gui;
        struct TouchInfo;
    }
}

namespace Vectoid {
namespace Gui {

//! Organizes its child GUI elements as a strip, either horizontally or vertically.
class Strip : public GuiElement {
  public:
    friend class Gui;
    
    Strip()                              = delete;
    Strip(const Strip &other)            = delete;
    Strip &operator=(const Strip &other) = delete;
    Strip(Strip &&other)                 = delete;
    Strip &operator=(Strip &&other)      = delete;
    ~Strip()                             = default;
    
    //! Adds the specified GUI element as child.
    void AddChild(const std::shared_ptr<GuiElement> &guiElement);
    
    void AddSceneGraphNodes(SceneGraph::CoordSys *guiCoordSys) override;
    RequiredSize UpdateRequiredSizes() override;
    void Layout(const Frame &frame) override;
    GuiElement *TouchedElement(const TouchInfo &touch) override;
    void OnTouchGestureBegan(const std::vector<const TouchInfo *> &touches) override;
    void OnTouchGestureMoved(const std::vector<const TouchInfo *> &touches) override;
    void OnTouchGestureEnded(const std::vector<const TouchInfo *> &touches) override;
    
  private:
    struct ChildInfo {
        std::shared_ptr<GuiElement> child;
        RequiredSize                requiredSize;
        
        ChildInfo(const std::shared_ptr<GuiElement> &child) : child{child} {}
        ChildInfo()                                  = delete;
        ChildInfo(const ChildInfo &other)            = default;
        ChildInfo &operator=(const ChildInfo &other) = default;
        ChildInfo(ChildInfo &&other)                 = default;
        ChildInfo &operator=(ChildInfo &&other)      = default;
        ~ChildInfo()                                 = default;
    };
    
    Strip(Orientation orientation, const std::shared_ptr<Context> &context);
    
    std::vector<ChildInfo> children_;
    bool                   vertical_;
    int                    numExtendable_;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_STRIP_H_
