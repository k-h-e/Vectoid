#include <Vectoid/SceneGraph/Vulkan/Camera.h>

#include <Vectoid/SceneGraph/Vulkan/Context.h>

using namespace std;

namespace Vectoid {
namespace SceneGraph {
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
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
