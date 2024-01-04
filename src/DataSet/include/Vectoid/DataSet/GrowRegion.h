///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_GROWREGION_H_
#define VECTOID_DATASET_GROWREGION_H_

#include <unordered_set>

namespace Vectoid {
namespace DataSet {

class Triangles;

//! Generic region growth algorithm.
void GrowRegion(Triangles *triangles, std::unordered_set<int> *inOutRegion,
                std::function<bool(int currentTriangle, int candidateTriangle, int sharedEdge)> criterion);

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_GROWREGION_H_
