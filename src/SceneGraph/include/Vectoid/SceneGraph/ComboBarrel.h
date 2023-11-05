///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_COMBOBARREL_H_
#define VECTOID_SCENEGRAPH_COMBOBARREL_H_

#include <optional>
#include <vector>
#include <Vectoid/Core/BoundingBox.h>
#include <Vectoid/SceneGraph/Geometry.h>

namespace Vectoid {
namespace SceneGraph {

class Glyphs;

//! UI element comparable to a combo-box.
class ComboBarrel : public Geometry {
  public:
    ComboBarrel()                                    = delete;
    ComboBarrel(const ComboBarrel &other)            = delete;
    ComboBarrel &operator=(const ComboBarrel &other) = delete;
    ComboBarrel(ComboBarrel &&other)                 = delete;
    ComboBarrel &operator=(ComboBarrel &&other)      = delete;
    ~ComboBarrel()                                   = default;
    
    //! Removes all items.
    void Clear();
    //! Adds the specified item.
    /*!
     *  \return The added item's ID.
     */
    int AddItem(const std::string &item);
    //! Tells the currently selected item, or <c>nullopt</c> in case no items are present.
    std::optional<int> Selection() const;
    //! Sets the selection as specified (if the given id exists).
    void SetSelection(int itemId);
    void SetPosition(float position);
    float Position() const;
    //! Sets the combo barrel's background color, including its alpha channel.
    void SetBackgroundColor(const Vectoid::Core::Vector<float> &color, float alpha);
    //! Sets the combo barrel's text color.
    void SetColor(const Vectoid::Core::Vector<float> &color);
    //! Tells the combo barrel's bounding box.
    Core::BoundingBox<float> BoundingBox() const;
    //! Enables/disables the combo barrel's frame.
    void EnableFrame(bool enabled);
    //! Sets the combo barrel's frame width.
    void SetFrameWidth(float width);
    
  protected:
    ComboBarrel(const std::shared_ptr<Context> &context, int width, int numVisibleOtherPerSide, float glyphWidth,
                float glyphHeight, const std::shared_ptr<Glyphs> &glyphs);
    
    int                      width_;
    int                      numVisibleOtherPerSide_;
    float                    glyphWidth_;
    float                    glyphHeight_;
    std::shared_ptr<Glyphs>  glyphs_;
    std::vector<std::string> items_;
    float                    position_;
    float                    itemAngle_;
    std::vector<float>       yCoords_;
    std::vector<float>       zCoords_;
    float                    barrelRadius_;
    Core::BoundingBox<float> boundingBox_;
    Core::Vector<float>      backgroundColor_;
    float                    backgroundAlpha_;
    Core::Vector<float>      color_;
    float                    frameWidth_;
    bool                     frameEnabled_;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_COMBOBARREL_H_
