///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_TRIANGLES_H_
#define VECTOID_DATASET_TRIANGLES_H_

#include <memory>
#include <optional>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <Vectoid/Core/TriangleHandlerInterface.h>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/DataSet/LineSegments.h>
#include <Vectoid/DataSet/SupportsBoundingBoxTreeInterface.h>
#include <Vectoid/DataSet/ThreeIds.h>
#include <Vectoid/DataSet/TwoIds.h>

namespace Vectoid {
    namespace Core {
        class ThreePoints;
        class TriangleProviderInterface;
    }
    namespace DataSet {
        class Points;
        class SimpleLineSegmentList;
        class ThreeIds;
    }
}

namespace Vectoid {
namespace DataSet {

//! Set of triangles in 3-space.
/*!
 *  Also maintains connectivity information.
 *
 *  As a triangle handler, it just accepts and adds triangles, but ignores any stream error.
 */
class Triangles : public virtual SupportsBoundingBoxTreeInterface,
                  public virtual Core::TriangleProviderInterface,
                  public virtual Core::TriangleHandlerInterface {
  public:
    Triangles();
    //! Initializes the set with the triangles from the specified provider.
    /*!
     *  Use <c>Core::TriangleProviderInterface::TriangleError()</c> to learn whether all triangles were copied
     *  successfully. If not, the <c>Triangles</c> object will be in sane state, yet triangles will be missing.
     */
    Triangles(Core::TriangleProviderInterface &triangleProvider);
    Triangles(const std::shared_ptr<Vectoid::DataSet::LineSegments> &edges);
    Triangles(const std::shared_ptr<Vectoid::DataSet::Points> &vertices);
    Triangles(const Triangles &other)            = delete;
    Triangles &operator=(const Triangles &other) = delete;
    Triangles(Triangles &&other)                 = delete;
    Triangles &operator=(Triangles &&other)      = delete;

    //! Adds the specified triangle (if it is not already present).
    /*!
     *  \return The triangle's index.
     */
    int Add(const Core::ThreePoints &triangle);
    //! Adds the triangles from the specified provider (those not already present).
    /*!
     *  \return
     *  <c>false</c> in case of failure. The <c>Triangles</c> object will then be in sane state, yet the triangles will
     *  only have been partially added.
     */
    bool Add(Core::TriangleProviderInterface &triangleProvider);
    //! Tells whether bad triangle connectivity has been detected.
    bool BadConnectivity();
    //! Retrieves the vertex data for the specified triangle.
    void GetTriangleVertices(int triangle, Core::ThreePoints &outVertices) const;
    //! Retrieves the vertex ids for the specified triangle.
    void GetTriangleVertexIds(int triangle, DataSet::ThreeIds &outVertexIds) const;
    //! Retrieves the specified triangle's edges.
    void GetTriangleEdges(int triangle, ThreeIds &outEdges);
    //! Retrieves the specified edge's vertices.
    void GetEdgeVertices(int edge, TwoIds &outVertices);
    //! Retrieves the specified triangle's neighbor triangle that shares the specified edge.
    /*!
     *  \return <c>-1</c> in case there is no such triangle.
     */
    int GetNeighbor(int triangle, int edge);
    //! Gets all triangles sharing the specified vertex.
    void GetTrianglesSharingVertex(int vertex, std::unordered_set<int> &outTriangles);
    //! Gets all triangles sharing the specified vertex.
    void GetTrianglesSharingVertex(const Core::Vector<float> &vertex, std::unordered_set<int> &outTriangles);
    //! Drops internal helper data structures in order to free up memory. These will automatically get re-generated when
    //! needed.
    void OptimizeForSpace();
    //! Creates an independent copy of the triangle set.
    std::unique_ptr<Triangles> Clone() const;
    //! Returns the underlying <c>LineSegments</c> object in which the triangle set stores its triangle edges.
    std::shared_ptr<LineSegments> Edges();
    //! Returns the underlying <c>Points</c> object in which the triangle set stores its vertices.
    std::shared_ptr<Points> Vertices();
    //! Attaches/de-attaches object to receive debug geometry.
    void SetDebugGeometry(const std::shared_ptr<SimpleLineSegmentList> &debugGeometry);

    // SupportsBoundingBoxTreeInterface...
    int Size() const override;
    void GetItemBoundingBox(int item, Core::BoundingBox<float> &outBoundingBox) const override;
    bool ComputeLineItemIntersection(const Core::Vector<float> &linePoint, const Core::Vector<float> &lineDirection,
                                     int item, bool &outIntersects, ItemIntersection &outIntersection) override;

    // TriangleProviderInterface...
    void PrepareToProvideTriangles() override;
    bool ProvideNextTriangle(Core::ThreePoints &outTriangle) override;
    void ProvideNormal(Core::Vector<float> &outNormal) override;
    bool TriangleError() override;

    // TriangleHandlerInterface...
    void OnTriangle(const Core::ThreePoints &triangle) override;
    void OnStreamError(K::Core::StreamInterface::Error error) override; 

  private:
    struct VertexInfo {
        int firstTriangle;

        VertexInfo()
                : firstTriangle(-1) {
            // Nop.
        }
        VertexInfo(const VertexInfo &other)            = default;
        VertexInfo &operator=(const VertexInfo &other) = default;
        VertexInfo(VertexInfo &&other)                 = default;
        VertexInfo &operator=(VertexInfo &&other)      = default;

        void RegisterTriangle(int triangle) {
            if (firstTriangle == -1) {
                firstTriangle = triangle;
            }
        }
    };
    struct EdgeInfo {
        int    triangle0;    // -1 if not set.
        int    triangle1;    // -1 if not set.

        EdgeInfo()
                : triangle0(-1),
                  triangle1(-1) {
            // Nop.
        }
        EdgeInfo(const EdgeInfo &other)            = default;
        EdgeInfo &operator=(const EdgeInfo &other) = default;
        EdgeInfo(EdgeInfo &&other)                 = default;
        EdgeInfo &operator=(EdgeInfo &&other)      = default;

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
        //! If the specified triangle contains the edge, and an adjacent triangle sharing the edge is present, that
        //! other triangle is returned. Otherwise <c>nullopt</c>.
        std::optional<int> OtherTriangle(int triangle) {
            if (triangle0 == triangle) {
                if (triangle1 != -1) {
                    return triangle1;
                }
            } else if (triangle1 == triangle) {
                return triangle0;
            }

            return std::nullopt;
        }
    };

    std::unordered_map<ThreeIds, int, ThreeIds::HashFunction> &TriangleMap();

    std::shared_ptr<Vectoid::DataSet::Points>                                  vertices_;
    std::shared_ptr<LineSegments>                                              edges_;
    std::vector<ThreeIds>                                                      triangles_;    // IDs are edge IDs.
    std::unique_ptr<std::unordered_map<ThreeIds, int, ThreeIds::HashFunction>> triangleMap_;
                                                                                   // Dynamically (re)generated.
    std::vector<EdgeInfo>                                                      edgeInfos_;
    std::vector<VertexInfo>                                                    vertexInfos_;
    bool                                                                       badConnectivity_;
    int                                                                        cursor_;
    Core::Vector<float>                                                        currentNormal_;
    std::shared_ptr<SimpleLineSegmentList>                                     debugGeometry_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_TRIANGLES_H_
