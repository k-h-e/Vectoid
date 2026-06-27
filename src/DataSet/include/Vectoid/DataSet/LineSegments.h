///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_LINESEGMENTS_H_
#define VECTOID_DATASET_LINESEGMENTS_H_

#include <memory>
#include <vector>
#include <unordered_map>
#include <Vectoid/Core/LineSegmentProviderInterface.h>
#include <Vectoid/DataSet/TwoIds.h>

namespace Vectoid {
namespace DataSet {

class Points;

//! Set of line segments in 3-space.
class LineSegments : public virtual Vectoid::Core::LineSegmentProviderInterface {
  public:
    LineSegments();
    LineSegments(const std::shared_ptr<Vectoid::DataSet::Points> &vertices);
    LineSegments(const LineSegments &other)            = delete;
    LineSegments &operator=(const LineSegments &other) = delete;
    LineSegments(LineSegments &&other)                 = delete;
    LineSegments &operator=(LineSegments &&other)      = delete;

    //! Adds the line segment (if it is not already present).
    /*!
     *  \return The line segment's index.
     */
    int Add(const Core::TwoPoints &segment);

    //! Adds the line segments from the specified provider (those not already present).
    /*!
     *  \return
     *  <c>false</c> in case of failure. The <c>LineSegments</c> object will then be in sane state, yet the line
     *  segments will only have been partially added.
     */
    bool Add(Core::LineSegmentProviderInterface &lineSegmentProvider);

    //! Tells the number of line segments.
    int Size() const;
    //! Returns the ID for the specified line segment, or <c>-1</c> in case the segment is not in the set.
    int Id(const TwoIds &segment);
    //! Retrieves vertex data for the specified segment.
    void GetSegmentVertices(int segment, Core::TwoPoints &outVertices);
    //! Retrieves the vertices for the specified segment.
    void GetSegmentVertices(int segment, TwoIds &outVertices);
    //! Drops internal helper data structures in order to free up memory. These will automatically get re-generated when
    //! needed.
    void OptimizeForSpace();
    //! Creates an independent copy of the line segment set.
    std::unique_ptr<LineSegments> Clone() const;
    //! Returns the underlying <c>Points</c> object in which the line segment set stores its vertices.
    std::shared_ptr<Points> Vertices();

    void PrepareToProvideLineSegments() override;
    bool ProvideNextLineSegment(Core::TwoPoints &outSegment) override;
    bool LineSegmentError() override;

  private:
    std::unordered_map<TwoIds, int, TwoIds::HashFunction> &SegmentMap();

    std::shared_ptr<Vectoid::DataSet::Points>                              vertices_;
    std::vector<TwoIds>                                                    segments_;
    std::unique_ptr<std::unordered_map<TwoIds, int, TwoIds::HashFunction>> segmentMap_;    // Dynamically (re)generated.
    int                                                                    cursor_;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_LINESEGMENTS_H_
