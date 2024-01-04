///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_TRIANGULATIONREFINERXY_H_
#define VECTOID_DATASET_TRIANGULATIONREFINERXY_H_

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <K/Core/Interface.h>

namespace Vectoid {
namespace Core {
    class TwoPoints;
    class LineSegmentProviderInterface;
}
}

namespace Vectoid {
namespace DataSet {

class Points;
class TriangleTreeXY;

//! Can further refine a triangulation in the <c>x/y</c> plane.
class TriangulationRefinerXY : public virtual K::Core::Interface {
  public:
    TriangulationRefinerXY(const std::shared_ptr<TriangleTreeXY> &triangleTree,
                           const std::shared_ptr<Points> &vertices);
    TriangulationRefinerXY(const TriangulationRefinerXY &other)             = delete;
    TriangulationRefinerXY &operator=(const TriangulationRefinerXY &other)  = delete;
    TriangulationRefinerXY(const TriangulationRefinerXY &&other)            = delete;
    TriangulationRefinerXY &operator=(const TriangulationRefinerXY &&other) = delete;

    bool EnforceEdge(const Core::TwoPoints &edge, std::vector<Core::TwoPoints> *outRefinedEdges);
    bool SelectSurface(Core::LineSegmentProviderInterface &boundaryCurve,
                       std::unordered_set<int> *outSelectedTriangles);

  private:
    std::shared_ptr<TriangleTreeXY>                  triangleTree_;
    std::shared_ptr<Points>                          vertices_;
    std::unordered_map<int, std::unordered_set<int>> vertexToTrianglesMap_;

    void BuildVertexToTrianglesMap();
    void AddTriangleToVertexToTrianglesMap(int triangleId);
    void RemoveTriangleFromVertexToTrianglesMap(int triangleId);
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_TRIANGULATIONREFINERXY_H_
