#include <Vectoid/Gui/Strip.h>

#include <Vectoid/Gui/Context.h>
#include <Vectoid/Gui/TouchInfo.h>

using std::shared_ptr;
using std::vector;
using Vectoid::SceneGraph::CoordSys;

namespace Vectoid {
namespace Gui {

Strip::Strip(Orientation orientation, const shared_ptr<Context> &context)
        : GuiElement{context},
          vertical_{orientation == Orientation::Vertical} {
    // Nop.
}

void Strip::AddChild(const shared_ptr<GuiElement> &guiElement) {
    children_.push_back(ChildInfo(guiElement));
    context_->SetLayoutRequired(true);
}

void Strip::AddSceneGraphNodes(CoordSys *guiCoordSys) {
    for (auto &info : children_) {
        info.child->AddSceneGraphNodes(guiCoordSys);
    }
}

Size Strip::UpdateRequiredSizes() {
    requiredSize_ = Size{};
    
    float offset{0.0f};
    bool  first{true};
    for (auto &info : children_) {
        Size size = info.child->UpdateRequiredSizes();
        
        info.offset       = offset;
        info.requiredSize = size;
        
        if (vertical_) {
            requiredSize_.height += size.height;
            if (!first) {
                requiredSize_.height += context_->Spacing();
            }
            if (size.width > requiredSize_.width) {
                requiredSize_.width = size.width;
            }
            offset = requiredSize_.height + context_->Spacing();
        } else {
            requiredSize_.width += size.width;
            if (!first) {
                requiredSize_.width += context_->Spacing();
            }
            if (size.height > requiredSize_.height) {
                requiredSize_.height = size.height;
            }
            offset = requiredSize_.width + context_->Spacing();
        }
        
        first  = false;
    }
    
    return requiredSize_;
}

void Strip::Layout(const Frame &frame) {
    frame_.position = frame.position;
    frame_.size     = requiredSize_;
    for (auto &info : children_) {
        Frame frame;
        if (vertical_) {
            frame = Frame{Position{frame_.position.x, frame_.position.y - info.offset}, info.requiredSize};
        } else {
            frame = Frame{Position{frame_.position.x + info.offset, frame_.position.y}, info.requiredSize};
        }
        info.child->Layout(frame);
    }
}

GuiElement *Strip::TouchedElement(const TouchInfo &touch) {
    if (frame_.Contains(touch.x, touch.y)) {
        for (auto &info : children_) {
            GuiElement *element = info.child->TouchedElement(touch);
            if (element) {
                return element;
            }
        }
    }
    
    return nullptr;
}

void Strip::OnTouchGestureBegan(const vector<const TouchInfo *> &touches) {
    // Nop.
}

void Strip::OnTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    // Nop.
}

void Strip::OnTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    // Nop.
}

}    // Namespace Gui.
}    // Namespace Vectoid.
