#ifndef VECTOID_DATASET_VERTEXSET_H_
#define VECTOID_DATASET_VERTEXSET_H_

#include <vector>
#include <unordered_map>
#include <Vectoid/Core/Vector.h>

#include <K/Core/Interface.h>

namespace Vectoid {
//! Data structures and algorithms for 3D data processing.
namespace DataSet {

//! Set of vertices in 3-space.
/*!
 *  Can grow dynamically.
 */
class VertexSet : public virtual K::Core::Interface {
  public:
    VertexSet();
    VertexSet(const VertexSet &other)             = delete;
    VertexSet &operator=(const VertexSet &other)  = delete;
    VertexSet(const VertexSet &&other)            = delete;
    VertexSet &operator=(const VertexSet &&other) = delete;

    //! Tells the number of vertices in the set.
    int Count();
    //! Adds the specified vertex, if it is not already present.
    /*!
     * \return
     * Id of the vertex inside the set.
     */
    int Add(const Core::Vector<float> &vertex);
    //! Gives access to the specified vertex.
    /*!
     *  The specified vertex id must lie in <c>[0, Count()]</c>.
     */
    const Core::Vector<float> &operator[](int index);
    //! Returns the id of the specified vertex, or <c>-1</c> in case the vertex is not in the set.
    int GetId(const Core::Vector<float> &vertex) const;

  private:
    struct VectorHashFunction {
        std::size_t operator()(const Core::Vector<float> &aVector) const {
            return aVector.Hash();
        }
    };

    std::vector<Core::Vector<float>>                                 vertices_;
    std::unordered_map<Core::Vector<float>, int, VectorHashFunction> vertexToIdMap_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_VERTEXSET_H_
