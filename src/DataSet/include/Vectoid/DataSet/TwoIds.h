#ifndef VECTOID_DATASET_TWOIDS_H_
#define VECTOID_DATASET_TWOIDS_H_

namespace Vectoid {
namespace DataSet {

//! Two data set item ids with significant ordering.
/*!
 *  \ingroup Vectoid
 */
class TwoIds {
  public:
    TwoIds() : id0(0), id1(0) {}
    TwoIds(int anId0, int anId1) : id0(anId0), id1(anId1) {}
    // Default copy/move, ok.

    int id0;
    int id1;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_TWOIDS_H_
