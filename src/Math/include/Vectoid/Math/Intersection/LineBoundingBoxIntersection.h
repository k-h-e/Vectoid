///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_MATH_INTERSECTION_LINEBOUNDINGBOXINTERSECTION_H_
#define VECTOID_MATH_INTERSECTION_LINEBOUNDINGBOXINTERSECTION_H_

namespace Vectoid {
    namespace Core {
        template<typename T> class BoundingBox;
        template<typename T> class Vector;
    }
}

namespace Vectoid {
namespace Math {
namespace Intersection {

//! Computes the intersection between a line and an axis-aligned bounding box.
class LineBoundingBoxIntersection {
  public:
    //! Computes the intersection between a line and an axis-aligned bounding box.
    /*!
     *  Uses the "slabs" method presented in <c>Geometric Tools for Computer Graphics</c> by <c>Schneider</c> and
     *  <c>Eberly</c>, including the corrections on <c>geometrictools.com</c>.
     *
     *  \return <c>false</c> in case the computation failed. The output parameter will then be undefined.
     */
    static bool Compute(const Core::Vector<float> &linePoint, const Core::Vector<float> &lineDirection,
                        const Core::BoundingBox<float> &boundingBox, bool &outIntersects);
};

}    // Namespace Intersection.
}    // Namespace Math.
}    // Namespace Vectoid.

#endif    // VECTOID_MATH_INTERSECTION_LINEBOUNDINGBOXINTERSECTION_H_
