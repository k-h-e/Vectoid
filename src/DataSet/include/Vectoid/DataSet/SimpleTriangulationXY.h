#ifndef VECTOID_DATASET_SIMPLETRIANGULATIONXY_H_
#define VECTOID_DATASET_SIMPLETRIANGULATIONXY_H_

#include <memory>
#include <unordered_set>

#include <K/Core/Interface.h>
#include <Vectoid/Core/BoundingBox.h>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/DataSet/VertexSet.h>
#include <Vectoid/DataSet/ThreeIds.h>

namespace Vectoid {
namespace DataSet {

//! Generates a triangulation for a set of vertices in the <c>x/y</c>-plane.
class SimpleTriangulationXY : public virtual Core::TriangleProviderInterface {
  public:
    SimpleTriangulationXY();
    SimpleTriangulationXY(const SimpleTriangulationXY &other)             = delete;
    SimpleTriangulationXY &operator=(const SimpleTriangulationXY &other)  = delete;
    SimpleTriangulationXY(const SimpleTriangulationXY &&other)            = delete;
    SimpleTriangulationXY &operator=(const SimpleTriangulationXY &&other) = delete;

    //! Adds the specified point in the <c>x/y</c>-plane (<c>z</c> coordinate will be zeroed).
    void Add(const Core::Vector<float> &point);
    //! Computes a triangulation for the points added so far.
    /*!
     *  \return
     *  <c>false</c> in case of failure. The triangulation will then be empty.
     */
    bool Compute();

    virtual void PrepareToProvideTriangles();
    virtual bool ProvideNextTriangle(Core::ThreePoints *outTriangle);
    virtual void ProvideNormal(Core::Vector<float> *outNormal);
    virtual bool TriangleError();

  private:
    struct TriangleInfo {
        ThreeIds vertexIds;
        ThreeIds children;       // The first numChildren of the ids are valid.
        int      numChildren;
        TriangleInfo() : numChildren(0) {}
        TriangleInfo(const ThreeIds &triangle) : vertexIds(triangle), numChildren(0) {}
        // Default copy/move, ok.
    };

    void CreateRootTriangles();
    bool LocateTriangleToSubdivide(const Core::Vector<float> &point, int *outTriangleId);
    bool ComputePointTriangleIntersection(const Core::Vector<float> &point, int triangleId, bool *outIntersects);
    void SubdivideTriangle(int triangleId, int vertexId);

    std::unique_ptr<VertexSet> vertexSet_;
    Core::BoundingBox<float>   boundingBox_;
    std::vector<TriangleInfo>  triangles_;
    std::vector<int>           rootTriangleIds_;
    int                        cursor_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_SIMPLETRIANGULATIONXY_H_
