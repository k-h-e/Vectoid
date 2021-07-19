#include <Vectoid/DataSet/Points.h>

#include <K/Core/Log.h>

using std::unordered_map;
using std::make_unique;
using std::to_string;
using K::Core::Log;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace DataSet {

Points::Points() {
    // Nop.
}

Points::Points(const Points &other)
        : points_(other.points_) {
    // Nop.
}

Points &Points::operator=(const Points &other) {
    points_ = other.points_;
    pointMap_.reset();
    return *this;
}

int Points::Size() const {
    return static_cast<int>(points_.size());
}

int Points::Add(const Core::Vector<float> &point) {
    auto *pointMap = PointMap();
    auto iter = pointMap->find(point);
    if (iter != pointMap->end()) {
        return iter->second;
    }
    else {
        int id = static_cast<int>(points_.size());
        points_.push_back(point);
        (*pointMap)[point] = id;
        return id;
    }
}

const Vector<float> &Points::operator[](int index) {
    assert((index >= 0) && (index < static_cast<int>(points_.size())));
    return points_[index];
}

int Points::Id(const Vector<float> &point) {
    auto *pointMap = PointMap();
    auto iterator = pointMap->find(point);
    if (iterator != pointMap->end()) {
        return iterator->second;
    }
    else {
        return -1;
    }
}

void Points::OptimizeForSpace() {
    Log::Print(Log::Level::Debug, this, []{ return "optimizing for space"; });
    pointMap_.reset();
}

unordered_map<Vector<float>, int, Vector<float>::HashFunction> *Points::PointMap() {
    if (!pointMap_) {
        Log::Print(Log::Level::Debug, this, []{ return "(re-)generating point map"; });
        pointMap_ = make_unique<unordered_map<Vector<float>, int, Vector<float>::HashFunction>>();
        for (int i = 0; i < static_cast<int>(points_.size()); ++i) {
             (*pointMap_)[points_[i]] = i;
        }
    }

    return pointMap_.get();
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
