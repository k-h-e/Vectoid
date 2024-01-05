///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_TWOIDS_H_
#define VECTOID_DATASET_TWOIDS_H_

#include <cassert>
#include <string>

namespace Vectoid {
namespace DataSet {

//! Two data set item ids with significant ordering.
class TwoIds {
  public:
    struct HashFunction;

    TwoIds() : id0(0), id1(0) {}
    TwoIds(int anId0, int anId1) : id0(anId0), id1(anId1) {}
    // Default copy/move, ok.

    bool operator==(const TwoIds &other) const {
        return (id0 == other.id0) && (id1 == other.id1);
    }

    std::size_t Hash() const {
        std::size_t hash = 17u;
        hash = hash*31u + std::hash<int>()(id0);
        hash = hash*31u + std::hash<int>()(id1);
        return hash;
    }

    TwoIds MakeCanonical() const {
        if (id0 < id1) {
            return TwoIds(id0, id1);
        }
        else {
            return TwoIds(id1, id0);
        }
    }

    bool Contains(int id) const {
        return (id0 == id) || (id1 == id);
    }

    int OtherId(int id) {
        if (id == id0) {
            return id1;
        }
        else {
            return id0;
        }
    }

    int SharedId(const TwoIds &other) {
        if ((id0 == other.id0) || (id0 == other.id1)) {
            return id0;
        } else if ((id1 == other.id0) || (id1 == other.id1)) {
            return id1;
        } else {
            assert(false);
        }
    }

    std::string ToString() const {
        return "(" + std::to_string(id0) + ", " + std::to_string(id1) + ")";
    }

    int id0;
    int id1;
};

struct TwoIds::HashFunction {
    std::size_t operator()(const TwoIds &twoIds) const {
        return twoIds.Hash();
    }
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_TWOIDS_H_
