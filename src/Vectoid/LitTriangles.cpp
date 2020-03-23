#include <kxm/Vectoid/LitTriangles.h>

using std::shared_ptr;

namespace kxm {
namespace Vectoid {

LitTriangles::LitTriangles(const shared_ptr<TriangleProviderInterface> &triangleProvider)
        : triangleProvider_(triangleProvider) {
    // Nop.
}

}    // Namespace Vectoid.
}    // Namespace kxm.
