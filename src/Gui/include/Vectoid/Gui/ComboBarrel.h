#ifndef VECTOID_GUI_COMBOBARREL_H_
#define VECTOID_GUI_COMBOBARREL_H_

#include <optional>
#include <Vectoid/Gui/GuiElement.h>

namespace Vectoid {
    namespace Gui {
        class Gui;
        struct TouchInfo;
    }
    namespace SceneGraph {
        class ComboBarrel;
    }
}

namespace Vectoid {
namespace Gui {

//! Combo-barrel GUI element, allowing to select one out of <c>n</c> options.
class ComboBarrel : public GuiElement {
  public:
    friend class Gui;
    
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
    
    void AddSceneGraphNodes(SceneGraph::CoordSys *guiCoordSys) override;
    Size UpdateRequiredSizes() override;
    void Layout(const Frame &frame) override;
    GuiElement *TouchedElement(const TouchInfo &touch) override;
    void OnTouchGestureBegan(const std::vector<const TouchInfo *> &touches) override;
    void OnTouchGestureMoved(const std::vector<const TouchInfo *> &touches) override;
    void OnTouchGestureEnded(const std::vector<const TouchInfo *> &touches) override;
    
  private:
    ComboBarrel(int width, int numVisibleOtherPerSide, Size glyphSize, const std::shared_ptr<Context> &context);
    void SetColors(bool active);
    
    std::shared_ptr<SceneGraph::ComboBarrel> comboBarrel_;
    std::shared_ptr<SceneGraph::CoordSys>    coordSys_;
    float                                    startPosition_;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_COMBOBARREL_H_
