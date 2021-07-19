#include <Vectoid/Math/Intersection/LineTriangleIntersection.h>

#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/Tools.h>
#include <Vectoid/Math/Intersection/PointTriangleIntersectionXY.h>

using Vectoid::Core::Vector;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::Tools;
using Vectoid::Math::Intersection::PointTriangleIntersectionXY;

namespace Vectoid {
namespace Math {
namespace Intersection {

bool LineTriangleIntersection::Compute(
        const Vector<float> &linePoint, const Vector<float> &lineDirection, const ThreePoints &triangle,
        bool *outIntersects, Vector<float> *outIntersectionPoint) {
    Vector<float> normal;
    triangle.ComputeNormal(&normal);
    if (!normal.Valid()) {
        return false;
    }

    Vector<float> u, v;
    Tools::CreateCoordinateSystem(DotProduct(lineDirection, normal) > 0 ? lineDirection : -lineDirection, &u, &v);
    ThreePoints triangleXY(Vector<float>(DotProduct(triangle.point0 - linePoint, u),
                                         DotProduct(triangle.point0 - linePoint, v), 0.0f),
                           Vector<float>(DotProduct(triangle.point1 - linePoint, u),
                                         DotProduct(triangle.point1 - linePoint, v), 0.0f),
                           Vector<float>(DotProduct(triangle.point2 - linePoint, u),
                                         DotProduct(triangle.point2 - linePoint, v), 0.0f));
    if (!PointTriangleIntersectionXY::Compute(Vector<float>(0.0f, 0.0f, 0.0f), triangleXY, outIntersects)) {
        return false;
    }

    if (*outIntersects) {
        Vector<float> barycentricCoordinates;
        if (!Tools::ComputeBarycentricCoordinates(Vector<float>(0.0f, 0.0f, 0.0f), triangleXY,
                                                  &barycentricCoordinates)) {
            return false;
        }
        *outIntersectionPoint =   barycentricCoordinates.x * triangle.point0
                                + barycentricCoordinates.y * triangle.point1
                                + barycentricCoordinates.z * triangle.point2;
    }

    return true;
}

}    // Namespace Intersection.
}    // Namespace Math.
}    // Namespace Vectoid.
