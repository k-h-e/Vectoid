#ifndef VECTOID_SCENEGRAPH_COMBOBARREL_H_
#define VECTOID_SCENEGRAPH_COMBOBARREL_H_

#include <optional>
#include <vector>
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
    
    //! Adds the specified item.
    /*!
     *  \return The added item's ID.
     */
    int AddItem(const std::string &item);
    //! Tells the currently selected item, or <c>nullopt</c> in case no items are present.
    std::optional<int> Selection() const;
    void SetPosition(float position);
    float Position() const;
    
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
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_COMBOBARREL_H_
