#include <kxm/Vectoid/Vulkan/PerspectiveProjection.h>

#include <kxm/Vectoid/Vulkan/Context.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

PerspectiveProjection::PerspectiveProjection(const shared_ptr<Context> &context)
    : context_(context) {
    // Nop.
}

void PerspectiveProjection::Render() {
    FullTransform objectTransformBackup(context_->ObjectTransform());
    if (parametersChanged_) {
        float windowWidth, windowHeight;
        ComputeWindowDimensions(&windowWidth, &windowHeight);
        transform_.SetFrustum(-windowWidth  / 2.0f, windowWidth  / 2.0f,
                              -windowHeight / 2.0f, windowHeight / 2.0f,
                              eyepointDistance_, eyepointDistance_ + viewingDepth_);
        transform_ = FullTransform(transform_, Transform(Vector(0.0, 0.0, -eyepointDistance_)));
        parametersChanged_ = false;
    }
    context_->UpdateObjectTransform(FullTransform(context_->ObjectTransform(), transform_));
    
    Vectoid::PerspectiveProjection::Render();
    
    context_->UpdateObjectTransform(objectTransformBackup);
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
