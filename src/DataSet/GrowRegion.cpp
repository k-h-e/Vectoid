///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/GrowRegion.h>

#include <Vectoid/DataSet/ThreeIds.h>
#include <Vectoid/DataSet/Triangles.h>

using std::function;
using std::unordered_set;
using std::vector;
using Vectoid::DataSet::ThreeIds;

namespace Vectoid {
namespace DataSet {

void GrowRegion(Triangles &triangles, unordered_set<int> &inOutRegion,
                function<bool(int currentTriangle, int candidateTriangle, int sharedEdge)> criterion) {
    unordered_set<int> toAdd;
    toAdd.swap(inOutRegion);

    ThreeIds edges;
    while (!toAdd.empty()) {
        int current = *toAdd.begin();
        toAdd.erase(current);
        inOutRegion.insert(current);
        triangles.GetTriangleEdges(current, edges);
        for (int i = 0; i < 3; ++i) {
            int edge = edges[i];
            int candidate = triangles.GetNeighbor(current, edge);
            if ((candidate != -1) && (inOutRegion.find(candidate) == inOutRegion.end())
                    && criterion(current, candidate, edge)) {
                toAdd.insert(candidate);
            }
        }
    }
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
