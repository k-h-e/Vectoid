#ifndef VECTOID_CORE_TOOLS_H_
#define VECTOID_CORE_TOOLS_H_

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
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_TOOLS_H_
