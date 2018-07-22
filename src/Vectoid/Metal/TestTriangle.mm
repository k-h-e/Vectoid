#include <kxm/Vectoid/Metal/TestTriangle.h>

using namespace std;

namespace kxm {
namespace Vectoid {
namespace Metal {

TestTriangle::TestTriangle(const shared_ptr<Context> &context)
        : Vectoid::TestTriangle(),
          context_(context) {
    // Nop.
}

void TestTriangle::Render() {
}

}    // Namespace Metal.
}    // Namespace Vectoid.
}    // Namespace kxm.
