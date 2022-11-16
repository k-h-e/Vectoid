#ifndef VECTOID_GUI_BUTTON_H_
#define VECTOID_GUI_BUTTON_H_

#include <string>
#include <Vectoid/Gui/GuiElement.h>

namespace Vectoid {
    namespace Gui {
        class Gui;
        struct TouchInfo;
    }
    namespace SceneGraph {
        class TextConsole;
    }
}

namespace Vectoid {
namespace Gui {

//! Button GUI element.
class Button : public GuiElement {
  public:
    friend class Gui;
    
    Button()                               = delete;
    Button(const Button &other)            = delete;
    Button &operator=(const Button &other) = delete;
    Button(Button &&other)                 = delete;
    Button &operator=(Button &&other)      = delete;
    ~Button()                              = default;
    
    void AddSceneGraphNodes(const std::shared_ptr<SceneGraph::CoordSys> &guiCoordSys) override;
    void UpdateRequiredSizes() override;
    void Layout(const Frame &frame) override;
    GuiElement *TouchedElement(const TouchInfo &touch) override;
    void OnTouchGestureBegan(const std::vector<const TouchInfo *> &touches) override;
    void OnTouchGestureMoved(const std::vector<const TouchInfo *> &touches) override;
    void OnTouchGestureEnded(const std::vector<const TouchInfo *> &touches) override;
    
  private:
    Button(const std::string &text, float glyphWidth, float glyphHeight, const std::shared_ptr<Context> &context);
    void SetBackgroundColor(bool active);
    
    std::shared_ptr<SceneGraph::TextConsole> textConsole_;
    std::shared_ptr<SceneGraph::CoordSys>    coordSys_;
    bool                                     touchInside_;
};

}    // Namespace Gui.
}    // Namespace Vectoid.

#endif    // VECTOID_GUI_BUTTON_H_
