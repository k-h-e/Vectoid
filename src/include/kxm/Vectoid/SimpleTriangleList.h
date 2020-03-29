#ifndef KXM_VECTOID_SIMPLETRIANGLELIST_H_
#define KXM_VECTOID_SIMPLETRIANGLELIST_H_

#include <vector>
#include <kxm/Vectoid/ThreePoints.h>
#include <kxm/Vectoid/TriangleProviderInterface.h>

namespace kxm {
namespace Vectoid {

//! Simple lists of triangles in 3-space that can be grown dynamically.
/*!
 *  \ingroup Vectoid
 */
class SimpleTriangleList : public virtual TriangleProviderInterface {
  public:
    SimpleTriangleList();
    SimpleTriangleList(const SimpleTriangleList &other)             = delete;
    SimpleTriangleList &operator=(const SimpleTriangleList &other)  = delete;
    SimpleTriangleList(const SimpleTriangleList &&other)            = delete;
    SimpleTriangleList &operator=(const SimpleTriangleList &&other) = delete;
    //! Appends the specified triangle to the list.
    void Add(const ThreePoints &triangle);
    virtual void PrepareToProvideTriangles();
    virtual bool ProvideNextTriangle(ThreePoints *outTriangle);
    virtual void ProvideNormal(Vector<float> *outNormal);
    virtual bool TriangleError();

  private:
    void EnsureNormalsValid();

    std::vector<ThreePoints>   triangles_;
    std::vector<Vector<float>> normals_;
    int                        cursor_;
    bool                       normalsValid_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_SIMPLETRIANGLELIST_H_
