#include <Vectoid/Gui/ComboBarrel.h>

#include <Vectoid/Gui/Context.h>
#include <Vectoid/SceneGraph/ComboBarrel.h>
#include <Vectoid/SceneGraph/RenderTargetInterface.h>

using std::make_shared;
using std::shared_ptr;

namespace Vectoid {
namespace Gui {

struct TouchInfo;

ComboBarrel::ComboBarrel(int width, int numVisibleOtherPerSide, float glyphWidth, float glyphHeight,
                         const std::shared_ptr<Context> &context)
        : GuiElement{context},
          startPosition_{0.0f} {
    comboBarrel_ = context_->renderTarget->NewComboBarrel(width, numVisibleOtherPerSide, glyphWidth, glyphHeight,
                                                          context_->glyphs);
}

void ComboBarrel::Clear() {
    comboBarrel_->Clear();
}

int ComboBarrel::AddItem(const std::string &item) {
    return comboBarrel_->AddItem(item);
}

void ComboBarrel::AddSceneGraphNodes(const std::shared_ptr<SceneGraph::CoordSys> &guiCoordSys) {
    
}

void ComboBarrel::UpdateRequiredSizes() {
    
}

void ComboBarrel::Layout(const Frame &frame) {
    
}

void ComboBarrel::OnTouchGestureBegan(const std::vector<const TouchInfo *> &touches) {
    startPosition_ = comboBarrel_->Position();
}

void ComboBarrel::OnTouchGestureMoved(const std::vector<const TouchInfo *> &touches) {
    /*
    Vector<float> current = projection_->TransformViewPortCoordinates(touchTable_[0]->x, touchTable_[0]->y);
    Vector<float> start   = projection_->TransformViewPortCoordinates(touchTable_[0]->startX,
                                                                      touchTable_[0]->startY);
    float t = (current.y - start.y) / projection_->WindowSize();
    comboBarrel_->SetPosition(barrelStartPosition_ + t*8.0f);
    if (handler_) {
        handler_->OnGraphicsViewRedrawRequired();
    }
     */
}

void ComboBarrel::OnTouchGestureEnded(const std::vector<const TouchInfo *> &touches) {
    
}

}    // Namespace Gui.
}    // Namespace Vectoid.
