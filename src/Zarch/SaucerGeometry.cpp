#include <kxm/Zarch/SaucerGeometry.h>

#include <kxm/Vectoid/Vector.h>

using namespace kxm::Vectoid;

namespace kxm {
namespace Zarch {

SaucerGeometry::SaucerGeometry() {
    static const float radius = 1.0f;
    float lastX, lastZ;
    for (int i = 0; i <= 8; ++i) {
        float angle = -22.5f + (float)(i*45);
        float x = radius * (float)cos(angle * 3.141592654f / 180.0f),
              z = radius * (float)sin(angle * 3.141592654f / 180.0f);
        if (i) {
            AddTriangle(Vector(0.0f,  .3f, 0.0f), Vector(x, 0.0f, z), Vector(lastX, 0.0f, lastZ),
                        i % 2 ? Vector( .2f,  .2f,  .8f) : Vector( .2f,  .8f,  .8f));

            AddTriangle(Vector(0.0f, -.3f, 0.0f), Vector(lastX, 0.0f, lastZ), Vector(x, 0.0f, z),
                        i % 2 ? Vector( .2f,  .8f,  .8f) : Vector( .2f,  .2f,  .8f));
        }
        lastX = x;
        lastZ = z;
    }
    Scale(.7f);
}

}    // Namespace Zarch.
}    // Namespace kxm.
