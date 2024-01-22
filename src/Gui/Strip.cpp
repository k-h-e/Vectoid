///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

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
          vertical_{orientation == Orientation::Vertical},
          numExtendable_{0} {
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

RequiredSize Strip::UpdateRequiredSizes() {
    requiredSize_ = RequiredSize{};
    
    numExtendable_ = 0;
    bool  first{true};
    for (auto &info : children_) {
        info.requiredSize = info.child->UpdateRequiredSizes();
        if (info.requiredSize.canUseMoreWidth) {
            requiredSize_.canUseMoreWidth = true;
        }
        if (info.requiredSize.canUseMoreHeight) {
            requiredSize_.canUseMoreHeight = true;
        }

        if (vertical_) {
            if (info.requiredSize.canUseMoreHeight) {
                ++numExtendable_;
            }

            requiredSize_.size.height += info.requiredSize.size.height;
            if (!first) {
                requiredSize_.size.height += context_->spacing;
            }
            if (info.requiredSize.size.width > requiredSize_.size.width) {
                requiredSize_.size.width = info.requiredSize.size.width;
            }
        } else {
            if (info.requiredSize.canUseMoreWidth) {
                ++numExtendable_;
            }

            requiredSize_.size.width += info.requiredSize.size.width;
            if (!first) {
                requiredSize_.size.width += context_->spacing;
            }
            if (info.requiredSize.size.height > requiredSize_.size.height) {
                requiredSize_.size.height = info.requiredSize.size.height;
            }
        }
        
        first = false;
    }
    
    return requiredSize_;
}

void Strip::Layout(const Frame &frame) {
    float extraWidth   { 0.0f };
    float extraHeight  { 0.0f };

    frame_.position = frame.position;
    frame_.size     = requiredSize_.size;
    if ((frame.size.width > frame_.size.width) && requiredSize_.canUseMoreWidth) {
        extraWidth        = frame.size.width - frame_.size.width;
        frame_.size.width = frame.size.width;
    }
    if ((frame.size.height > frame_.size.height) && requiredSize_.canUseMoreHeight) {
        extraHeight        = frame.size.height - frame_.size.height;
        frame_.size.height = frame.size.height;
    }

    int   numToExtend  { 0    };
    float extraPortion { 0.0f };
    if (numExtendable_ > 0) {
        numToExtend = numExtendable_;
        if (vertical_) {
            extraPortion = extraHeight / static_cast<float>(numToExtend);
        } else {
            extraPortion = extraWidth / static_cast<float>(numToExtend);
        }
    }

    float offset{0.0f};
    for (auto &info : children_) {
        Frame frame;
        if (vertical_) {
            float height = info.requiredSize.size.height;
            if (info.requiredSize.canUseMoreHeight && (numToExtend > 0)) {
                float extra = (numToExtend > 1) ? extraPortion : extraHeight;
                height      += extra;
                extraHeight -= extra;
                --numToExtend;
            }
            frame = Frame{Position{frame_.position.x, frame_.position.y - offset}, Size{frame_.size.width, height}};
            offset += height;
        } else {
            float width = info.requiredSize.size.width;
            if (info.requiredSize.canUseMoreWidth && (numToExtend > 0)) {
                float extra = (numToExtend > 1) ? extraPortion : extraWidth;
                width      += extra;
                extraWidth -= extra;
                --numToExtend;
            }
            frame = Frame{Position{frame_.position.x + offset, frame_.position.y}, Size{width, frame_.size.height}};
            offset += width;
        }

        info.child->Layout(frame);

        offset += context_->spacing;
    }

    (void) extraWidth;
    (void) extraHeight;
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
    (void) touches;
    // Nop.
}

void Strip::OnTouchGestureMoved(const vector<const TouchInfo *> &touches) {
    (void) touches;
    // Nop.
}

void Strip::OnTouchGestureEnded(const vector<const TouchInfo *> &touches) {
    (void) touches;
    // Nop.
}

}    // Namespace Gui.
}    // Namespace Vectoid.
