///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/SimpleLineSegmentList.h>

using Vectoid::Core::Vector;
using Vectoid::Core::TwoPoints;
using Vectoid::Core::BoundingBox;

namespace Vectoid {
namespace DataSet {

SimpleLineSegmentList::SimpleLineSegmentList()
        : cursor_(-1) {
    // Nop.
}

void SimpleLineSegmentList::Add(const TwoPoints &lineSegment) {
    lineSegments_.push_back(lineSegment);
    boundingBox_.Grow(lineSegment.point0);
    boundingBox_.Grow(lineSegment.point1);
}

int SimpleLineSegmentList::Size() const {
    return static_cast<int>(lineSegments_.size());
}

void SimpleLineSegmentList::PrepareToProvideLineSegments() {
    cursor_ = -1;
}

bool SimpleLineSegmentList::ProvideNextLineSegment(TwoPoints *outLineSegment) {
    ++cursor_;
    if (cursor_ < static_cast<int>(lineSegments_.size())) {
        *outLineSegment = lineSegments_[cursor_];
        return true;
    }
    else {
        return false;
    }
}

bool SimpleLineSegmentList::LineSegmentError() {
    return false;
}

void SimpleLineSegmentList::GetBoundingBox(BoundingBox<float> *outBoundingBox) {
    *outBoundingBox = boundingBox_;
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
