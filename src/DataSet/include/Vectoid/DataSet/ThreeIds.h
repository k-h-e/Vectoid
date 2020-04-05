#ifndef VECTOID_DATASET_THREEIDS_H_
#define VECTOID_DATASET_THREEIDS_H_

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

    //! Tells whether the specified id is one of the three ids.
    bool Contains(int id) {
        return (id0 == id) || (id1 == id) || (id2 == id);
    }

    int id0;
    int id1;
    int id2;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_THREEIDS_H_
