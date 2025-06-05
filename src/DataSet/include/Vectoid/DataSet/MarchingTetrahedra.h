///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_MARCHINGTETRAHEDRA_H_
#define VECTOID_DATASET_MARCHINGTETRAHEDRA_H_

#include <vector>

#include <K/Core/Interface.h>
#include <Vectoid/Core/Transform.h>
#include <Vectoid/DataSet/TwoIds.h>

namespace Vectoid {
    namespace Core {
        class TriangleHandlerInterface;
    }
    namespace DataSet {
        class LineSegments;
        class RegularScalarGrid;
        class ThreeIds;
    }
}

namespace Vectoid {
namespace DataSet {

//! Extracts an iso-surface from a rectilinear 3D scalar field using a method similar to Marching Cubes, but subdivides
//! each cube into tetrahedra prior to generating triangles.
class MarchingTetrahedra : public virtual K::Core::Interface {
  public:
    MarchingTetrahedra();
    MarchingTetrahedra(const MarchingTetrahedra &other)            = delete;
    MarchingTetrahedra &operator=(const MarchingTetrahedra &other) = delete;
    MarchingTetrahedra(MarchingTetrahedra &&other)                 = delete;
    MarchingTetrahedra &operator=(MarchingTetrahedra &&other)      = delete;
    ~MarchingTetrahedra()                                          = default;

    //! Extracts from the specified cube grid the iso-surface for the specified iso-value.
    /*!
     *  Will not call <c>OnStreamError()</c> on the triangle handler.
     */
    void ExtractIsoSurface(RegularScalarGrid &grid, float isoValue, Core::TriangleHandlerInterface &triangleHandler);
    //! Extracts from the specified cube the iso-surface for the specified iso-value.
    /*!
     *  Will not call <c>OnStreamError()</c> on the triangle handler.
     */
    void ExtractIsoSurface(const DataSet::ThreeIds &cube, RegularScalarGrid &grid, float isoValue,
                           Core::TriangleHandlerInterface &triangleHandler);
    //! Attaches/de-attaches object to receive debug geometry.
    void SetDebugGeometry(const std::shared_ptr<LineSegments> &debugGeometry);

  private:
    static constexpr unsigned int bitValues[8] { 1u, 2u, 4u, 8u, 16u, 32u, 64u, 128u }; 

    struct Case {
        std::vector<int> edges;

        // Default copy/move, ok.
    };

    void SetUpCube();
    void GenerateTrianglesForCube();
    void GenerateTrianglesForTetrahedron(int vertexIndex0, int vertexIndex1, int vertexIndex2, int vertexIndex3);
    void AddCase(unsigned int caseId, const std::vector<int> &edges);
    void AddMetaCubeTetrahedra(const std::vector<int> &tetrahedra);
    void RotateMetaCubeTetrahedra(Core::Axis axis, std::vector<int> &tetrahedra);
    void CollectCubeTetrahedra(int x, int y, int z, const std::vector<int> &tetrahedra);

    Case                           cases_[16];
    TwoIds                         edgeVertices_[6];
    std::vector<int>               metaCubeTetrahedra_;
    std::vector<int>               cubeTetrahedra_[2][2][2];
    RegularScalarGrid              *grid_;
    float                          isoValue_;
    Core::TriangleHandlerInterface *triangleHandler_;
    int                            xCursor_;
    int                            yCursor_;
    int                            zCursor_;
    std::vector<int>               *cubePattern_;
    Core::Vector<float>            vertices_[8];
    float                          vertexValues_[8];
    int                            vertexMap_[4];
    Core::Vector<float>            edgeIntersections_[6];
    std::shared_ptr<LineSegments>  debugGeometry_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_MARCHINGTETRAHEDRA_H_
