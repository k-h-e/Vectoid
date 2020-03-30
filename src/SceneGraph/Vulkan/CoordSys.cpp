#include <Vectoid/SceneGraph/Vulkan/CoordSys.h>

#include <Vectoid/SceneGraph/Vulkan/Context.h>

using namespace std;

namespace Vectoid {
namespace SceneGraph {
namespace Vulkan {

CoordSys::CoordSys(const shared_ptr<Context> &context)
        : Vectoid::CoordSys(),
          context_(context) {
    // Nop.
}

void CoordSys::Render() {
    FullTransform objectTransformBackup(context_->ObjectTransform());
    context_->UpdateObjectTransform(FullTransform(context_->ObjectTransform(), transform_));
    
    Vectoid::CoordSys::Render();
    
    context_->UpdateObjectTransform(objectTransformBackup);
}

}    // Namespace Vulkan.
}    // Namespace SceneGraph.
}    // Namespace Vectoid.
