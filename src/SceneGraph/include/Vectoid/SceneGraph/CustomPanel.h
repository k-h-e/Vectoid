///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_CUSTOMPANEL_H_
#define VECTOID_SCENEGRAPH_CUSTOMPANEL_H_

#include <Vectoid/Core/Vector.h>
#include <Vectoid/SceneGraph/Geometry.h>

namespace Vectoid {
    namespace Core {
        template<typename T> class BoundingBox;
    }
}

namespace Vectoid {
namespace SceneGraph {

//! Custom panel geometry.
class CustomPanel : public Geometry {
  public:
    CustomPanel(const std::shared_ptr<Context> &context, float width, float height);
    CustomPanel()                                    = delete;
    CustomPanel(const CustomPanel &other)            = delete;
    CustomPanel &operator=(const CustomPanel &other) = delete;
    CustomPanel(CustomPanel &&other)                 = delete;
    CustomPanel &operator=(CustomPanel &&other)      = delete;
    ~CustomPanel()                                   = default;
    
    //! Tells the panel's bounding box.
    Core::BoundingBox<float> BoundingBox() const;
    //! Sets the panel's background color, including its alpha channel.
    void SetBackgroundColor(const Vectoid::Core::Vector<float> &color, float alpha);
     //! Toggles rendering of the panel frame, default is off.
    void EnableFrame(bool enabled);
    //! Sets the panel's frame color.
    void SetFrameColor(const Vectoid::Core::Vector<float> &color);
    //! Sets the panel's frame width.
    void SetFrameWidth(float width);
    
  protected:
    float                        width_;
    float                        height_;
    float                        frameWidth_;
    Vectoid::Core::Vector<float> backgroundColor_;
    float                        backgroundAlpha_;
    Vectoid::Core::Vector<float> frameColor_;
    bool                         frameEnabled_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_CUSTOMPANEL_H_
