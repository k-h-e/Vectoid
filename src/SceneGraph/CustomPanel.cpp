#include <Vectoid/SceneGraph/CustomPanel.h>

#include <K/Core/NumberTools.h>

using std::shared_ptr;
using K::Core::NumberTools;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace SceneGraph {

CustomPanel::CustomPanel(const shared_ptr<Context> &context, float width, float height)
        : Geometry{context},
          width_{width},
          height_{height} {
    NumberTools::ClampMin(&width_, 0.0f);
    NumberTools::ClampMin(&height_, 0.0f);
}

float CustomPanel::Width() const {
    return width_;
}

float CustomPanel::Height() const {
    return height_;
}

void CustomPanel::SetBackgroundColor(const Vector<float> &color, float alpha) {
    backgroundColor_ = color;
    NumberTools::Clamp(&backgroundColor_.x, 0.0f, 1.0f);
    NumberTools::Clamp(&backgroundColor_.y, 0.0f, 1.0f);
    NumberTools::Clamp(&backgroundColor_.z, 0.0f, 1.0f);

    backgroundAlpha_ = alpha;
    NumberTools::Clamp(&backgroundAlpha_, 0.0f, 1.0f);
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
