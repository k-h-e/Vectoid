#include <kxm/Vectoid/Vulkan/CoordSys.h>

#include <kxm/Vectoid/Vulkan/Context.h>

using namespace std;

namespace kxm {
namespace Vectoid {
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
}    // Namespace Vectoid.
}    // Namespace kxm.
