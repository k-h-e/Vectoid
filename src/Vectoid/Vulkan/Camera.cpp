#include <kxm/Vectoid/Vulkan/Camera.h>

#include <kxm/Vectoid/Vulkan/Context.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

Camera::Camera(const shared_ptr<Context> &context)
        : Vectoid::Camera(),
          context_(context) {
    // Nop.
}

void Camera::Render() {
    FullTransform objectTransformBackup(context_->ObjectTransform());
    Transform inverse(Transform::InitAsInverse, transform_);
    context_->UpdateObjectTransform(FullTransform(context_->ObjectTransform(), inverse));

    Vectoid::Camera::Render();

    context_->UpdateObjectTransform(objectTransformBackup);
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
