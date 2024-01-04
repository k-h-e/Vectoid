///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Core/LineSegmentOffsetter.h>

#include <Vectoid/Core/TwoPoints.h>

namespace Vectoid {
namespace Core {

LineSegmentOffsetter::LineSegmentOffsetter(const std::shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider,
                                           const Vector<float> &offset)
        : lineSegmentProvider_(lineSegmentProvider),
          offset_(offset) {
    // Nop.
}

void LineSegmentOffsetter::PrepareToProvideLineSegments() {
    lineSegmentProvider_->PrepareToProvideLineSegments();
}

bool LineSegmentOffsetter::ProvideNextLineSegment(TwoPoints *outLineSegment) {
    if (lineSegmentProvider_->ProvideNextLineSegment(outLineSegment)) {
        outLineSegment->point0 += offset_;
        outLineSegment->point1 += offset_;
        return true;
    }

    return false;
}

bool LineSegmentOffsetter::LineSegmentError() {
    return lineSegmentProvider_->LineSegmentError();
}

}    // Namespace Core.
}    // Namespace Vectoid.
