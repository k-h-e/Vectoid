#ifndef VECTOID_DATASET_TRIANGULATIONREFINERXY_H_
#define VECTOID_DATASET_TRIANGULATIONREFINERXY_H_

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <K/Core/Interface.h>

namespace Vectoid {
namespace Core {
    class LineSegmentProviderInterface;
}
}

namespace Vectoid {
namespace DataSet {

class TriangleTreeXY;
class VertexSet;

//! Can further refine a triangulation in the <c>x/y</c> plane.
/*!
 *  \ingroup Vectoid
 */
class TriangulationRefinerXY : public virtual K::Core::Interface {
  public:
    TriangulationRefinerXY(const std::shared_ptr<TriangleTreeXY> &triangleTree,
                           const std::shared_ptr<VertexSet> &vertexSet);
    TriangulationRefinerXY(const TriangulationRefinerXY &other)             = delete;
    TriangulationRefinerXY &operator=(const TriangulationRefinerXY &other)  = delete;
    TriangulationRefinerXY(const TriangulationRefinerXY &&other)            = delete;
    TriangulationRefinerXY &operator=(const TriangulationRefinerXY &&other) = delete;

    bool SelectSurface(Core::LineSegmentProviderInterface &boundaryCurve,
                       std::unordered_set<int> *outSelectedTriangles);

  private:
    std::shared_ptr<TriangleTreeXY>                  triangleTree_;
    std::shared_ptr<VertexSet>                       vertexSet_;
    std::unordered_map<int, std::unordered_set<int>> vertexToTrianglesMap_;

    void BuildVertexToTrianglesMap();
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_TRIANGULATIONREFINERXY_H_
