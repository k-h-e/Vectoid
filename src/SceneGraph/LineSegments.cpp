///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/SceneGraph/LineSegments.h>

using std::shared_ptr;

using K::Core::NumberTools;
using Vectoid::Core::LineSegmentProviderInterface;

namespace Vectoid {
namespace SceneGraph {

LineSegments::LineSegments(const shared_ptr<Context> &context,
                           const shared_ptr<LineSegmentProviderInterface> &lineSegmentProvider)
        : Geometry{context},
          lineSegmentProvider_{lineSegmentProvider},
          color_{.8f, .8f, .8f},
          lineWidth_{1.0f},
          dynamicGeometryEnabled_{false} {
    // Nop.
}

void LineSegments::SetColor(const Core::Vector<float> &color) {
    color_ = color;
}

void LineSegments::SetLineWidth(float width) {
    NumberTools::ClampMin(width, 1.0f);
    lineWidth_ = width;
}

void LineSegments::EnableDynamicGeometry(bool enabled) {
    dynamicGeometryEnabled_ = enabled;
}

}    // Namespace SceneGraph.
}    // Namespace Vectoid.
