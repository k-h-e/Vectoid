///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/LineSegments.h>

using std::shared_ptr;
using Vectoid::Core::LineSegmentProviderInterface;

namespace Vectoid {
namespace SceneGraph {

LineSegments::LineSegments(const shared_ptr<Context> &context,
                           const shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider)
        : Geometry{context},
          lineSegmentProvider_{lineSegmentProvider},
          color_{.8f, .8f, .8f},
          dynamicGeometryEnabled_{false} {
    // Nop.
}

void LineSegments::SetColor(const Core::Vector<float> &color) {
    color_ = color;
}

void LineSegments::EnableDynamicGeometry(bool enabled) {
    dynamicGeometryEnabled_ = enabled;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
