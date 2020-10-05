#ifndef VECTOID_DATASET_TWOIDS_H_
#define VECTOID_DATASET_TWOIDS_H_

using std::to_string;

namespace Vectoid {
namespace DataSet {

//! Two data set item ids with significant ordering.
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

    std::size_t Hash() const {
        std::size_t hash = 17u;
        hash = hash*31u + std::hash<int>()(id0);
        hash = hash*31u + std::hash<int>()(id1);
        return hash;
    }

    std::string ToString() const {
        return "(" + to_string(id0) + ", " + to_string(id1) + ")";
    }

    int id0;
    int id1;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_TWOIDS_H_
