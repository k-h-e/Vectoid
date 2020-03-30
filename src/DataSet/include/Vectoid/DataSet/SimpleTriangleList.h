#ifndef VECTOID_DATASET_SIMPLETRIANGLELIST_H_
#define VECTOID_DATASET_SIMPLETRIANGLELIST_H_

#include <vector>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/TriangleProviderInterface.h>

namespace Vectoid {
namespace DataSet {

//! Simple list of triangles in 3-space that can be grown dynamically.
/*!
 *  \ingroup Vectoid
 */
class SimpleTriangleList : public virtual Core::TriangleProviderInterface {
  public:
    SimpleTriangleList();
    SimpleTriangleList(const SimpleTriangleList &other)             = delete;
    SimpleTriangleList &operator=(const SimpleTriangleList &other)  = delete;
    SimpleTriangleList(const SimpleTriangleList &&other)            = delete;
    SimpleTriangleList &operator=(const SimpleTriangleList &&other) = delete;
    //! Appends the specified triangle to the list.
    void Add(const Core::ThreePoints &triangle);
    virtual void PrepareToProvideTriangles();
    virtual bool ProvideNextTriangle(Core::ThreePoints *outTriangle);
    virtual void ProvideNormal(Core::Vector<float> *outNormal);
    virtual bool TriangleError();

  private:
    void EnsureNormalsValid();

    std::vector<Core::ThreePoints>   triangles_;
    std::vector<Core::Vector<float>> normals_;
    int                              cursor_;
    bool                             normalsValid_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_SIMPLETRIANGLELIST_H_
