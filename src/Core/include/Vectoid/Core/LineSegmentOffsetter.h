///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_LINESEGMENTOFFSETTER_H_
#define VECTOID_CORE_LINESEGMENTOFFSETTER_H_

#include <memory>
#include <Vectoid/Core/LineSegmentProviderInterface.h>
#include <Vectoid/Core/Vector.h>

namespace Vectoid {
namespace Core {

//! Line segment provider (decorator) applying an offset translation to the line segments.
class LineSegmentOffsetter : public virtual LineSegmentProviderInterface {
  public:
    LineSegmentOffsetter(const std::shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider,
                         const Vector<float> &offset);

    void PrepareToProvideLineSegments();
    bool ProvideNextLineSegment(TwoPoints *outLineSegment);
    bool LineSegmentError();

  private:
    std::shared_ptr<LineSegmentProviderInterface> lineSegmentProvider_;
    Vector<float>                                 offset_;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_LINESEGMENTOFFSETTER_H_
