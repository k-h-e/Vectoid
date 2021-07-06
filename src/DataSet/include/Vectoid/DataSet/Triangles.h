#ifndef VECTOID_DATASET_TRIANGLES_H_
#define VECTOID_DATASET_TRIANGLES_H_

#include <memory>
#include <vector>
#include <unordered_map>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/DataSet/ThreeIds.h>
#include <Vectoid/DataSet/TwoIds.h>
#include <Vectoid/DataSet/VertexSet.h>

namespace Vectoid {

namespace Core {
    class ThreePoints;
}

namespace DataSet {

//! Holds a set of triangles together with connectivity information.
/*!
 *  Intended for sets of triangular elements forming surfaces in 3D.
 */
class Triangles : public virtual Vectoid::Core::TriangleProviderInterface {
  public:
    Triangles(const std::shared_ptr<Vectoid::DataSet::VertexSet> &vertices);
    Triangles(const Triangles &other)            = delete;
    Triangles &operator=(const Triangles &other) = delete;
    Triangles(Triangles &&other)                 = delete;
    Triangles &operator=(Triangles &&other)      = delete;

    //! Adds the specified triangle (if it is not already present).
    /*!
     *  \return The triangle's index.
     */
    int Add(const Core::ThreePoints &triangle);
    //! Tells whether bad triangle connectivity has been detected.
    bool BadConnectivity();
    //! Tells the number of triangles.
    int TriangleCount();
    //! Retrieves the vertex data for the specified triangle.
    void GetTriangleVertices(int triangle, Core::ThreePoints *outVertices);

    void PrepareToProvideTriangles() override;
    bool ProvideNextTriangle(Core::ThreePoints *outTriangle) override;
    void ProvideNormal(Core::Vector<float> *outNormal) override;
    bool TriangleError() override;

  private:
    struct EdgeInfo {
        TwoIds vertices;
        int    triangle0;    // -1 if not set.
        int    triangle1;    // -1 if not set.

        EdgeInfo(const TwoIds &someVertices)
                : vertices(someVertices),
                  triangle0(-1),
                  triangle1(-1) {
            // Nop.
        }
        bool AddTriangle(int triangle) {
            if (triangle0 == -1) {
                triangle0 = triangle;
                return true;
            } else if (triangle1 == -1) {
                triangle1 = triangle;
                return true;
            } else {
                return false;
            }
        }
    };

    std::unordered_map<TwoIds, int, TwoIds::HashFunction> *EdgeMap();
    std::unordered_map<ThreeIds, int, ThreeIds::HashFunction> *TriangleMap();

    std::shared_ptr<Vectoid::DataSet::VertexSet>                               vertices_;
    std::vector<EdgeInfo>                                                      edges_;
    std::vector<ThreeIds>                                                      triangles_;    // IDs are edge IDs.
    std::unique_ptr<std::unordered_map<TwoIds, int, TwoIds::HashFunction>>     edgeMap_;
                                                                                   // Dynamically (re)generated.
    std::unique_ptr<std::unordered_map<ThreeIds, int, ThreeIds::HashFunction>> triangleMap_;
                                                                                   // Dynamically (re)generated.
    bool                                                                       badConnectivity_;
    int                                                                        cursor_;
    Core::Vector<float>                                                        currentNormal_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_TRIANGLES_H_
