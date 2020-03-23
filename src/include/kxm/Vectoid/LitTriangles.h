#ifndef KXM_VECTOID_LITTRIANGLES_H_
#define KXM_VECTOID_LITTRIANGLES_H_

#include <memory>
#include <kxm/Vectoid/GeometryInterface.h>

namespace kxm {
namespace Vectoid {

class TriangleProviderInterface;

//! Renders lit triangles.
/*!
 *  \ingroup Vectoid
 */
class LitTriangles : public virtual GeometryInterface {
  public:
    LitTriangles(const LitTriangles &other)            = delete;
    LitTriangles &operator=(const LitTriangles &other) = delete;
    LitTriangles(LitTriangles &&other)                 = delete;
    LitTriangles &operator=(LitTriangles &&other)      = delete;

  protected:
    LitTriangles(const std::shared_ptr<TriangleProviderInterface> &triangleProvider);

    std::shared_ptr<TriangleProviderInterface> triangleProvider_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_LITTRIANGLES_H_
