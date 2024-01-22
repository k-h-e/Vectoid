///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_GUI_EMPTYSPACE_H_
#define VECTOID_GUI_EMPTYSPACE_H_

#include <Vectoid/Gui/GuiElement.h>

namespace Vectoid {
namespace Gui {

//! Empty space.
class EmptySpace : public GuiElement {
  public:
    friend class Gui;
    
    EmptySpace()                                   = delete;
    EmptySpace(const EmptySpace &other)            = delete;
    EmptySpace &operator=(const EmptySpace &other) = delete;
    EmptySpace(EmptySpace &&other)                 = delete;
    EmptySpace &operator=(EmptySpace &&other)      = delete;
    ~EmptySpace()                                  = default;
    
    void AddSceneGraphNodes(SceneGraph::CoordSys *guiCoordSys) override;
    RequiredSize UpdateRequiredSizes() override;
    void Layout(const Frame &frame) override;
    GuiElement *TouchedElement(const TouchInfo &touch) override;
    void OnTouchGestureBegan(const std::vector<const TouchInfo *> &touches) override;
    void OnTouchGestureMoved(const std::vector<const TouchInfo *> &touches) override;
    void OnTouchGestureEnded(const std::vector<const TouchInfo *> &touches) override;
    
  private:
    EmptySpace(bool extendsHorizontally, bool extendsVertically, const std::shared_ptr<Context> &context);
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_EMPTYSPACE_H_
