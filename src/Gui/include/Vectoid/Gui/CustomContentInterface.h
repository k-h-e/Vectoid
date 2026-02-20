///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_GUI_CUSTOMCONTENTINTERFACE_H_
#define VECTOID_GUI_CUSTOMCONTENTINTERFACE_H_

#include <chrono>
#include <memory>
#include <K/Core/Interface.h>

namespace Vectoid {
    namespace Core {
        template<typename T> class Vector;
    }
    namespace SceneGraph {
        class GroupNode;
    }
    namespace Gui {
        struct Size;
    }
}

namespace Vectoid {
namespace Gui {

//! Interface to custom content for GUI elements.
class CustomContentInterface : public virtual K::Core::Interface {
  public:
    //! Tells the content size.
    virtual Size GetSize() const = 0;
    //! Sets the content color.
    virtual void SetColor(const Vectoid::Core::Vector<float> &color) = 0;
    //! Animates the content according to the specified time since the last frame.
    virtual void Animate(float deltaTimeS) = 0;
    //! Resets the animation state.
    virtual void ResetAnimation() = 0;
    //! Adds to the specified group node scene graph nodes that represent the custom content.
    virtual void AddSceneGraphNodes(SceneGraph::GroupNode *groupNode) = 0;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_CUSTOMCONTENTINTERFACE_H_
