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

    bool operator==(const TwoIds &other) const {
        return (id0 == other.id0) && (id1 == other.id1);
    }

    TwoIds MakeCanonical() const {
        if (id0 < id1) {
            return TwoIds(id0, id1);
        }
        else {
            return TwoIds(id1, id0);
        }
    }

    std::size_t Hash() const {
        std::size_t hash = 17u;
        hash = hash*31u + std::hash<int>()(id0);
        hash = hash*31u + std::hash<int>()(id1);
        return hash;
    }

    int id0;
    int id1;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_TWOIDS_H_
