#include <kxm/Vectoid/Metal/Camera.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Metal {

Camera::Camera(const shared_ptr<Context> &context)
        : Vectoid::Camera(),
          context_(context) {
    //Nop.
}

void Camera::Render() {
}

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.
