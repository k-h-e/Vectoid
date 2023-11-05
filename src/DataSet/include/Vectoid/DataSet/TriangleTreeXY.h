///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_TRIANGLETREEXY_H_
#define VECTOID_DATASET_TRIANGLETREEXY_H_

#include <memory>
#include <vector>
#include <Vectoid/Core/TriangleProviderInterface.h>
#include <Vectoid/DataSet/ThreeIds.h>

namespace Vectoid {
namespace Core {
    template<typename T> class Vector;
    class ThreePoints;
}
}

namespace Vectoid {
namespace DataSet {

class Points;

//! Tree of triangles in the <c>x/y</c>-plane.
class TriangleTreeXY : public virtual Core::TriangleProviderInterface {
  public:
    struct TriangleInfo {
        // Counter-clockwise ordering...
        ThreeIds vertices;
        // Adjacent triangle n shares the edge (vertex_n, vertex_n+1). Id -1 is special and means "no adjacent triangle
        // sharing this edge"...
        ThreeIds adjacentTriangles;
        // Id -1 is special and means "this child is not present". If a triangle has n children, then these will be
        // referenced by child_0, ..., child_n-1...
        ThreeIds children;

        TriangleInfo(int vertex0, int vertex1, int vertex2);
        // Default copy/move, ok.

        //! Tells whether the tringle has children.
        bool HasChildren();
        //! Returns the vertex for the specified index, which must be non-negative (modulo <c>3</c> for <c>i</c> in
        //! <c>{3, 4, 5}</c> will get applied).
        int GetVertex(int i);
        //! Returns the adjacent triangle for the specified index, which must be non-negative (modulo <c>3</c> for
        //! <c>i</c> in <c>{3, 4, 5}</c> will get applied).
        int GetAdjacentTriangle(int i);
        //! Sets the adjacent triangle for the specified index, which must be non-negative (modulo <c>3</c> for
        //! <c>i</c> in <c>{3, 4, 5}</c> will get applied).
        void SetAdjacentTriangle(int i, int anAdjacentTriangle);
        int GetChild(int i);
        void AddChild(int child);
    };

    TriangleTreeXY(const std::shared_ptr<Points> &vertices);
    TriangleTreeXY(const TriangleTreeXY &other)             = delete;
    TriangleTreeXY &operator=(const TriangleTreeXY &other)  = delete;
    TriangleTreeXY(const TriangleTreeXY &&other)            = delete;
    TriangleTreeXY &operator=(const TriangleTreeXY &&other) = delete;

    TriangleInfo &operator[](int index);
    //! Tells the number of all triangles in the tree (not just the leaves!).
    int Count() const;
    int LocateTriangle(const Core::Vector<float> &point, int rootTriangleId);
    void GetIdsForSharedEdge(int triangle0Id, int triangle1Id, int *outSharedEdge0Id, int *outSharedEdge1Id);
    void UpdateTriangleAdjacency(int triangleToUpdateId, int oldAdjacentTriangleId, int newAdjacentTriangleId);
    int AddTriangle(int parentTriangleId);

    //! For non-negative values the method returns the value modulo <c>3</c>. Efficiency degrades with higher values.
    static int Mod3(int value);

    virtual void PrepareToProvideTriangles();
    virtual bool ProvideNextTriangle(Core::ThreePoints *outTriangle);
    virtual void ProvideNormal(Core::Vector<float> *outNormal);
    virtual bool TriangleError();

  private:
    std::shared_ptr<Points>    vertices_;
    std::vector<TriangleInfo>  triangles_;
    int                        cursor_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_TRIANGLETREEXY_H_
