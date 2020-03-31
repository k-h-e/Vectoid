#ifndef VECTOID_DATASET_DELAUNEYTRIANGULATION_H_
#define VECTOID_DATASET_DELAUNEYTRIANGULATION_H_

#include <memory>

#include <K/Core/Interface.h>
#include <Vectoid/DataSet/VertexSet.h>

namespace Vectoid {
namespace DataSet {

//! Generates a Delauney triangulation for a set of vertices in the <c>x/y</c>-plane.
/*!
 *  \ingroup Vectoid
 */
class DelauneyTriangulation : public virtual K::Core::Interface {
  public:
    DelauneyTriangulation();
    DelauneyTriangulation(const DelauneyTriangulation &other)             = delete;
    DelauneyTriangulation &operator=(const DelauneyTriangulation &other)  = delete;
    DelauneyTriangulation(const DelauneyTriangulation &&other)            = delete;
    DelauneyTriangulation &operator=(const DelauneyTriangulation &&other) = delete;

    //! Adds the specified point in the <c>x/y</c>-plane (<c>z</c> coordinate will be zeroed).
    void Add(const Core::Vector<float> &point);
    //! Computes the Delauney triangulation for the points added so far.
    /*!
     *  \return
     *  <c>false</c> in case of failure. The triangulation will then be empty.
     */
    bool Compute();

  private:
    std::unique_ptr<VertexSet> vertexSet_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_DELAUNEYTRIANGULATION_H_
