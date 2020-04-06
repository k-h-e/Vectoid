#ifndef VECTOID_DATASET_THREEIDS_H_
#define VECTOID_DATASET_THREEIDS_H_

#include <string>
#include <Vectoid/DataSet/TwoIds.h>

using std::to_string;

namespace Vectoid {
namespace DataSet {

//! Three data set item ids with significant ordering.
/*!
 *  \ingroup Vectoid
 */
class ThreeIds {
  public:
    ThreeIds() : id0(0), id1(0), id2(0) {}
    ThreeIds(int anId0, int anId1, int anId2) : id0(anId0), id1(anId1), id2(anId2) {}
    // Default copy/move, ok.

    int &operator[](int index) {
        switch (index) {
            case 1:
                return id1;
            case 2:
                return id2;
            default:
                return id0;
        }
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
        return "(" + to_string(id0) + ", " + to_string(id1) + ", " + to_string(id2) + ")";
    }

    int id0;
    int id1;
    int id2;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_THREEIDS_H_
