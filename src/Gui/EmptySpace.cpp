///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Gui/EmptySpace.h>

using std::vector;
using Vectoid::SceneGraph::CoordSys;

namespace Vectoid {
namespace Gui {

EmptySpace::EmptySpace(bool extendsHorizontally, bool extendsVertically, const std::shared_ptr<Context> &context)
        : GuiElement{context} {
    if (extendsHorizontally) {
        requiredSize_.canUseMoreWidth = true;
    }
    if (extendsVertically) {
        requiredSize_.canUseMoreHeight = true;
    }
}

void EmptySpace::AddSceneGraphNodes(CoordSys *guiCoordSys) {
    (void) guiCoordSys;

    // Nop.
}

RequiredSize EmptySpace::UpdateRequiredSizes() {
    return requiredSize_;
}

void EmptySpace::Layout(const Frame &frame) {
    frame_.position = frame.position;
    frame_.size     = requiredSize_.size;
}

GuiElement *EmptySpace::TouchedElement(const TouchInfo &touch) {
    (void) touch;
    return nullptr;
}

void EmptySpace::OnTouchGestureBegan(const vector<const TouchInfo *> &touches) {
    (void) touches;
    // Nop.
}

void EmptySpace::OnTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    (void) touches;
    // Nop.
}

void EmptySpace::OnTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    (void) touches;
    // Nop.
}

}    // Namespace Gui.
}    // Namespace Vectoid.
