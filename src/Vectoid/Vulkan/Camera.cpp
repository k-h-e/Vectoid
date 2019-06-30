#include <kxm/Vectoid/Vulkan/Camera.h>

#include <kxm/Core/logging.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Vulkan {

Camera::Camera(const shared_ptr<Context> &context)
        : Vectoid::Camera(),
          context_(context) {
    //Nop.
}

void Camera::Render() {
    Core::Log().Stream() << "Vulkan::Camera::Render()" << endl;
    Vectoid::Camera::Render();
}

}    // Namespace Vulkan.
}    // Namespace Vectoid.
}    // Namespace kxm.
