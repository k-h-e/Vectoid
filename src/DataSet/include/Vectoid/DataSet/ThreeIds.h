///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_THREEIDS_H_
#define VECTOID_DATASET_THREEIDS_H_

#include <limits>
#include <string>

#include <Vectoid/Core/Tools.h>
#include <Vectoid/DataSet/TwoIds.h>

namespace Vectoid {
namespace DataSet {

//! Three data set item ids with significant ordering.
class ThreeIds {
  public:
    struct HashFunction;

    ThreeIds() : id0(0), id1(0), id2(0) {}
    ThreeIds(int anId0, int anId1, int anId2) : id0(anId0), id1(anId1), id2(anId2) {}
    // Default copy/move, ok.

    bool operator==(const ThreeIds &other) const {
        return (id0 == other.id0) && (id1 == other.id1) && (id2 == other.id2);
    }

    std::size_t Hash() const {
        std::size_t hash = 17u;
        hash = hash*31u + std::hash<int>()(id0);
        hash = hash*31u + std::hash<int>()(id1);
        hash = hash*31u + std::hash<int>()(id2);
        return hash;
    }

    //! Gives access to the specified ID. Does mod 3 on index.
    int &operator[](int index) {
        switch (Core::Tools::IndexMod3(index)) {
            case 1:
                return id1;
            case 2:
                return id2;
            default:
                return id0;
        }
    }

    //! Gives access to the specified ID. Does mod 3 on index.
    const int &operator[](int index) const {
        switch (Core::Tools::IndexMod3(index)) {
            case 1:
                return id1;
            case 2:
                return id2;
            default:
                return id0;
        }
    }

    ThreeIds MakeCanonical() const {
        int min      = std::numeric_limits<int>::max();
        int minIndex = -1;
        for (int i = 0; i < 3 ; ++i) {
            if ((*this)[i] <= min) {
                min      = (*this)[i];
                minIndex = i;
            }
        }

        return ThreeIds((*this)[minIndex], (*this)[minIndex + 1], (*this)[minIndex + 2]);
    }

    //! Tells whether the specified id is one of the three ids.
    bool Contains(int id) {
        return (id0 == id) || (id1 == id) || (id2 == id);
    }

    TwoIds GetEdge(int index) const {
        switch (index) {
            case 1:
                return TwoIds(id1, id2);
            case 2:
                return TwoIds(id2, id0);
            default:
                return TwoIds(id0, id1);
        }
    }

    std::string ToString() const {
        return "(" + std::to_string(id0) + ", " + std::to_string(id1) + ", " + std::to_string(id2) + ")";
    }

    int id0;
    int id1;
    int id2;
};

struct ThreeIds::HashFunction {
    std::size_t operator()(const ThreeIds &threeIds) const {
        return threeIds.Hash();
    }
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_THREEIDS_H_
