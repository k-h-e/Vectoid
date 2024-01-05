///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_TOOLS_H_
#define VECTOID_CORE_TOOLS_H_

#include <optional>

namespace Vectoid {
namespace Core {

template<typename T> class Vector;
class ThreePoints;

//! Various tool functions.
class Tools {
  public:
    //! Creates unit-length vectors <c>u</c> and <c>v</c> so that <c>(u, v, direction)</c> form a right hand coordinate
    //! system.
    /*!
     * \param direction
     * Unit-length direction vector.
     */
    static void CreateCoordinateSystem(const Vector<float> &direction, Vector<float> *outU, Vector<float> *outV);
    //! Returns the angle in degrees, in <c>[0, 360)</c>, between vectors <c>(1, 0)</c> and <c>(x, y)</c>, or
    //! <c>nullopt</c> in case that angle can not be determined.
    /*!
     *  Returns 0 degrees for <c>(1, 0)</c>, 45 degrees for <c>(1, 1)</c>, 90 degrees for <c>(0, 1)</c>, and so on.
     */
    static std::optional<float> PolarAngle(float x, float y);
    //! Computes the barycentric coordinates of a point in the x/y plane with respect to a triangle in the x/y plane.
    /*!
     *  Taken from Christer Ericson's book "Real-Time Collision Detection".
     *
     *  \return <c>false</c> in case the computation failed. The output parameter will then be undefined.
     */
    static bool ComputeBarycentricCoordinates(const Vector<float> &pointXY, const ThreePoints &triangleXY,
                                              Vector<float> *outBarycentricCoordinates);
    //! Returns the index in <c>[0, 2]</c> according to modulo 3. Use only with input close to <c>[0, 2]</c>.
    static int IndexMod3(int index);
    //! Returns the index in <c>[0, 1]</c> according to modulo 2. Use only with input close to <c>[0, 1]</c>.
    static int IndexMod2(int index);
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_TOOLS_H_
