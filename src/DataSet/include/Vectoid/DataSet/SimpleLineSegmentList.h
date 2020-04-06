#ifndef VECTOID_DATASET_SIMPLELINESEGMENTLIST_H_
#define VECTOID_DATASET_SIMPLELINESEGMENTLIST_H_

#include <vector>
#include <Vectoid/Core/TwoPoints.h>
#include <Vectoid/Core/LineSegmentProviderInterface.h>
#include <Vectoid/Core/HasBoundingBoxInterface.h>
#include <Vectoid/Core/BoundingBox.h>

namespace Vectoid {
namespace DataSet {

//! Simple list of line segments in 3-space that can be grown dynamically.
/*!
 *  \ingroup Vectoid
 */
class SimpleLineSegmentList : public virtual Core::LineSegmentProviderInterface,
                              public virtual Core::HasBoundingBoxInterface {
  public:
    SimpleLineSegmentList();
    SimpleLineSegmentList(const SimpleLineSegmentList &other)             = delete;
    SimpleLineSegmentList &operator=(const SimpleLineSegmentList &other)  = delete;
    SimpleLineSegmentList(const SimpleLineSegmentList &&other)            = delete;
    SimpleLineSegmentList &operator=(const SimpleLineSegmentList &&other) = delete;
    //! Appends the specified line segment to the list.
    void Add(const Core::TwoPoints &lineSegment);
    virtual void PrepareToProvideLineSegments();
    virtual bool ProvideNextLineSegment(Core::TwoPoints *outLineSegment);
    virtual bool LineSegmentError();
    virtual void GetBoundingBox(Core::BoundingBox<float> *outBoundingBox);

  private:
    std::vector<Core::TwoPoints> lineSegments_;
    Core::BoundingBox<float>     boundingBox_;
    int                          cursor_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_SIMPLELINESEGMENTLIST_H_