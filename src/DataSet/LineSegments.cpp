#include <Vectoid/DataSet/LineSegments.h>

#include <K/Core/Log.h>
#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/DataSet/Points.h>

using std::shared_ptr;
using std::make_unique;
using std::unordered_map;
using std::to_string;
using K::Core::Log;
using Vectoid::Core::TwoPoints;
using Vectoid::DataSet::TwoIds;

namespace Vectoid {
namespace DataSet {

LineSegments::LineSegments(const shared_ptr<Points> &vertices)
        : vertices_(vertices),
          cursor_(-1) {
    // Nop.
}

int LineSegments::Add(const TwoPoints &segment) {
    auto segmentCanonical = TwoIds(vertices_->Add(segment.point0), vertices_->Add(segment.point1)).MakeCanonical();

    int  segmentId = -1;
    auto *segmentMap = SegmentMap();
    auto iter = segmentMap->find(segmentCanonical);
    if (iter == segmentMap->end()) {
        segmentId = static_cast<int>(segments_.size());
        segments_.push_back(segmentCanonical);
        (*segmentMap)[segmentCanonical] = segmentId;
    } else {
        segmentId = iter->second;
    }

    return segmentId;
}

int LineSegments::Count() {
    return static_cast<int>(segments_.size());
}

int LineSegments::Id(const TwoIds &segment) {
    auto *segmentMap = SegmentMap();
    auto iter = segmentMap->find(segment.MakeCanonical());
    if (iter != segmentMap->end()) {
        return iter->second;
    } else {
        return -1;
    }
}

void LineSegments::GetSegmentVertices(int segment, TwoPoints *outVertices) {
    TwoIds &vertices = segments_[segment];
    outVertices->point0 = (*vertices_)[vertices.id0];
    outVertices->point1 = (*vertices_)[vertices.id1];
}

void LineSegments::GetSegmentVertices(int segment, TwoIds *outVertices) {
    *outVertices = segments_[segment];
}

void LineSegments::OptimizeForSpace() {
    Log::Print(Log::Level::Debug, this, []{ return "optimizing for space"; });
    segmentMap_.reset();
    vertices_->OptimizeForSpace();
}

shared_ptr<Points> LineSegments::Vertices() {
    return vertices_;
}

void LineSegments::PrepareToProvideLineSegments() {
    cursor_ = -1;
}

bool LineSegments::ProvideNextLineSegment(TwoPoints *outSegment) {
    if (cursor_ + 1 < Count()) {
        ++cursor_;
        GetSegmentVertices(cursor_, outSegment);
        return true;
    }

    return false;
}

bool LineSegments::LineSegmentError() {
    return false;
}

unordered_map<TwoIds, int, TwoIds::HashFunction> *LineSegments::SegmentMap() {
    if (!segmentMap_) {
        Log::Print(Log::Level::Debug, this, []{ return "(re-)generating segment map"; });
        segmentMap_ = make_unique<unordered_map<TwoIds, int, TwoIds::HashFunction>>();
        for (int i = 0; i < static_cast<int>(segments_.size()); ++i) {
            (*segmentMap_)[segments_[i]] = i;
        }
    }

    return segmentMap_.get();
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
