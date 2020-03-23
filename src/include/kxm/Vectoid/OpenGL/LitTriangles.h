#ifndef KXM_VECTOID_OPENGL_LITTRIANGLES_H_
#define KXM_VECTOID_OPENGL_LITTRIANGLES_H_

#include <kxm/Vectoid/LitTriangles.h>

namespace kxm {
namespace Vectoid {
namespace OpenGL {

//! Renders lit triangles.
/*!
 *  \ingroup VectoidOpenGL
 */
class LitTriangles : public Vectoid::LitTriangles {
  public:
    LitTriangles(const std::shared_ptr<TriangleProviderInterface> &triangleProvider);
    LitTriangles(const LitTriangles &other)            = delete;
    LitTriangles &operator=(const LitTriangles &other) = delete;
    LitTriangles(LitTriangles &&other)                 = delete;
    LitTriangles &operator=(LitTriangles &&other)      = delete;
    virtual void Render();
};

}    // Namespace OpenGL.
}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_LITTRIANGLES_H_
