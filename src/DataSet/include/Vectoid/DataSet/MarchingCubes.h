///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_MARCHINGCUBES_H_
#define VECTOID_DATASET_MARCHINGCUBES_H_

#include <vector>

#include <K/Core/Interface.h>
#include <Vectoid/DataSet/TwoIds.h>

namespace Vectoid {
namespace DataSet {

//! Implements the <c>Marching Cubes</c> algorithm for extracting an iso-surface from a 3D scalar field where the sample
//! points are arranged in a regular grid.
/*!
    Note that as "weird" cube cases are currently ignored it is possible that the resulting iso-surface has "holes".
    The missing cases can be added later if needed.
 */

class MarchingCubes : public virtual K::Core::Interface {
  public:
    MarchingCubes();
    MarchingCubes(const MarchingCubes &other)            = delete;
    MarchingCubes &operator=(const MarchingCubes &other) = delete;
    MarchingCubes(MarchingCubes &&other)                 = delete;
    MarchingCubes &operator=(MarchingCubes &&other)      = delete;
    ~MarchingCubes()                                     = default;

  private:
    void AddCasesFor(unsigned int protoCase, const std::vector<int> edges);

    std::vector<TwoIds> edgeVertices_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_MARCHINGCUBES_H_
