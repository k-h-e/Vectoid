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
    namespace DataSet {
        class RegularScalarGrid;
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

    //! Extracts from the specified grid the iso-surface for the specified iso-value.
    /*!
     *  The dimensions of the grid must be odd, so that the number of cubes in each dimension is even. Otherwise,
     *  the extractor will not output any triangles. This is because we always combine eight neighboring cubes into a
     *  "meta cube" in order to perform the tetrahedron subdivision.
     */
    void ExtractIsoSurface(const RegularScalarGrid &grid, float isoValue);

  private:
    static constexpr unsigned int bitValues[8] { 1u, 2u, 4u, 8u, 16u, 32u, 64u, 128u }; 

    struct Case {
        std::vector<int> edges;

        // Default copy/move, ok.
    };

    void SetUpMetaCube();
    void GenerateTrianglesForMetaCube();
    void GenerateTrianglesForTetrahedron(int vertexIndex0, int vertexIndex1, int vertexIndex2, int vertexIndex3);
    void AddCase(unsigned int caseId, const std::vector<int> &edges);
    void AddTetrahedra(const std::vector<int> &tetrahedra);
    void RotateTetrahedra(Core::Axis axis, std::vector<int> &tetrahedra);

    Case                    cases_[16];
    TwoIds                  edgeVertices_[6];
    std::vector<int>        tetrahedronSubDivision_;
    const RegularScalarGrid *grid_;
    float                   isoValue_;
    int                     xCursor_;
    int                     yCursor_;
    int                     zCursor_;
    Core::Vector<float>     vertices_[27];
    float                   vertexValues_[27];
    int                     vertexMap_[4];
    Core::Vector<float>     edgeIntersections_[6];
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_MARCHINGTETRAHEDRA_H_
