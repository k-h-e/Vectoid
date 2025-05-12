///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/MarchingCubes.h>

using std::vector;

namespace Vectoid {
namespace DataSet {

MarchingCubes::MarchingCubes() {
    edgeVertices_.push_back(TwoIds{0, 1});
    edgeVertices_.push_back(TwoIds{1, 2});
    edgeVertices_.push_back(TwoIds{2, 3});
    edgeVertices_.push_back(TwoIds{3, 0});
    edgeVertices_.push_back(TwoIds{4, 5});
    edgeVertices_.push_back(TwoIds{5, 6});
    edgeVertices_.push_back(TwoIds{6, 7});
    edgeVertices_.push_back(TwoIds{7, 4});
    edgeVertices_.push_back(TwoIds{0, 4});
    edgeVertices_.push_back(TwoIds{1, 5});
    edgeVertices_.push_back(TwoIds{2, 6});
    edgeVertices_.push_back(TwoIds{3, 7});

    AddCasesFor(  0u, { });
    AddCasesFor(  1u, { 8, 0, 3 });
    AddCasesFor(  3u, { 8, 9, 3, 3, 9, 1 });
    AddCasesFor(  5u, { 8, 0, 3, 2, 1, 10 });
    AddCasesFor( 50u, { 5, 1, 7, 7, 1, 8, 1, 0, 8 });

    AddCasesFor( 51u, { 3, 7, 5, 3, 5, 1 });
    AddCasesFor( 58u, { 3, 11, 2, 5, 1, 7, 7, 1, 8, 1, 0, 8 });
    AddCasesFor(165u, { 8, 0, 3, 11, 7, 6, 2, 1, 10, 4, 5, 9 });
    AddCasesFor(177u, { 3, 11, 6, 3, 6, 0, 0, 6, 5, 0, 5, 9 });
    //AddCasesFor(178u, { });    // Weird case.

    AddCasesFor( 65u, { 8, 0, 3, 5, 6, 10 });
    AddCasesFor( 67u, { 8, 9, 3, 3, 9, 1, 5, 6, 10 });
    AddCasesFor( 74u, { 3, 2, 11, 0, 9, 1, 5, 6, 10 });
    //AddCasesFor(105u, { });    // Classic ambiguous case.
    //AddCasesFor(113u, { });    // Weird case.
}

// ---

void MarchingCubes::AddCasesFor(unsigned int protoCase, const vector<int> edges) {
    (void) protoCase;
    (void) edges;
}

}    // Namespace Vectoid.
}    // Namespace K.
