#include <Vectoid/SceneGraph/Vulkan/Camera.h>

#include <Vectoid/SceneGraph/Vulkan/Context.h>

using namespace std;
using Vectoid::Core::Transform;
using Vectoid::Core::FullTransform;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

Camera::Camera(const shared_ptr<Context> &context)
        : Vectoid::SceneGraph::Camera(),
          context_(context) {
    // Nop.
}

void Camera::Render() {
    FullTransform objectTransformBackup(context_->ObjectTransform());
    Transform<float> inverse(Transform<float>::InitAsInverse, transform_);
    context_->UpdateObjectTransform(FullTransform(context_->ObjectTransform(), inverse));

    Vectoid::SceneGraph::Camera::Render();

    context_->UpdateObjectTransform(objectTransformBackup);
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
