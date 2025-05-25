///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Core/Tools.h>

#include <cmath>
#include <vector>

#include <K/Core/NumberTools.h>
#include <Vectoid/Core/BoundingBox.h>
#include <Vectoid/Core/PointHandlerInterface.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/Transform.h>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/Math/Intersection/LineTriangleIntersection.h>

using std::abs;
using std::atan2;
using std::isfinite;
using std::numeric_limits;
using std::nullopt;
using std::optional;
using std::swap;
using std::vector;
using K::Core::NumberTools;
using Vectoid::Core::BoundingBox;
using Vectoid::Math::Intersection::LineTriangleIntersection;

namespace Vectoid {
namespace Core {

void Tools::CreateCoordinateSystem(const Vector<float> &direction, Vector<float> &outU, Vector<float> &outV) {
    vector<Vector<float>> bases;
    bases.push_back(Vector<float>(1.0f, 0.0f, 0.0f));
    bases.push_back(Vector<float>(0.0f, 1.0f, 0.0f));
    bases.push_back(Vector<float>(0.0f, 0.0f, 1.0f));
    Vector<float> bestBase;
    float max = -1.0f;
    for (auto &base : bases) {
        float area = CrossProduct(direction, base).Length();
        if (area > max) {
            max      = area;
            bestBase = base;
        }
    }

    outU = CrossProduct(direction, bestBase);
    outU.Normalize();
    outV = CrossProduct(direction, outU);
    outV.Normalize();
}

optional<float> Tools::PolarAngle(float x, float y) {
    float angleRadians = atan2(y, x);
    if (errno != EDOM) {
        float angleDeg = angleRadians * 180.0f / static_cast<float>(NumberTools::pi);    // In [-180, +180].
        if (angleDeg < 0.0f) {
            angleDeg += 360.0f;
        }
        if (angleDeg >= 360.0f) {
            angleDeg = 0.0f;
        }

        if (isfinite(angleDeg)) {
            return angleDeg;
        }
    }

    return nullopt;
}

bool Tools::ComputeBarycentricCoordinates(const Vector<float> &pointXY, const ThreePoints &triangleXY,
                                          Vector<float> *outBarycentricCoordinates) {
    Vector<float> v0 = triangleXY.point1 - triangleXY.point0;
    Vector<float> v1 = triangleXY.point2 - triangleXY.point0;
    Vector<float> v2 = pointXY           - triangleXY.point0;
    v0.z = 0.0f;
    v1.z = 0.0f;
    v2.z = 0.0f;

    float d00 = DotProduct(v0, v0);
    float d01 = DotProduct(v0, v1);
    float d11 = DotProduct(v1, v1);
    float d20 = DotProduct(v2, v0);
    float d21 = DotProduct(v2, v1);
    float denom = d00*d11 - d01*d01;
    outBarycentricCoordinates->y = (d11*d20 - d01*d21) / denom;
    outBarycentricCoordinates->z = (d00*d21 - d01*d20) / denom;
    outBarycentricCoordinates->x = 1.0f - outBarycentricCoordinates->y - outBarycentricCoordinates->z;
    return outBarycentricCoordinates->Valid();
}

void Tools::SampleTrianglePoints(const ThreePoints &triangle, float maxDistance, PointHandlerInterface &pointHandler) {
    Vector<float> normal { triangle.Normal() };
    if (!normal.Valid()) {
        return;
    }

    // Sample points from the triangle edges (also, compute minimum height)...
    float minHeight { numeric_limits<float>::max() };
    for (int i = 0; i < 3; ++i) {
        Vector<float> start { triangle[i] };
        Vector<float> end   { triangle[i + 1] };
        Vector<float> top   { triangle[i + 2] };

        pointHandler.OnPoint(start);

        float length { (end - start).Length() };
        if (length == 0.0f) {
            return;
        }
        float step { maxDistance / length };
        if (step == 0.0f) {
            return;
        }

        Vector<float> heightDirection { CrossProduct(end - start, normal) };
        heightDirection.Normalize();
        if (heightDirection.Valid()) {
            float height { abs(DotProduct(top - start, heightDirection)) };
            if (height < minHeight) {
                minHeight = height;
            }
        }

        // We establish a defined ordering so adjacent triangles get the same points for their shared edge...
        bool haveToSwap { false };
        if (start.x < end.x) {
            haveToSwap = false;
        } else if (start.x > end.x) {
            haveToSwap = true;
        } else {
            if (start.y < end.y) {
                haveToSwap = false;
            } else if (start.y > end.y) {
                haveToSwap = true;
            } else {
                haveToSwap = (start.z > end.z);
            }
        }
        if (haveToSwap) {
            swap(start, end);
        }

        for (float t = step; t < 1.0f; t += step) {
            pointHandler.OnPoint(CombineAffine(t, start, end));
            
        }
    }

    // Sample points from the triangle's interior...
    if (minHeight >= maxDistance) {
        Vector<float> u;
        Vector<float> v;
        Tools::CreateCoordinateSystem(normal, u, v);
        Transform<float> transform2{u, v, normal};
        Transform<float> transform3{Axis::Z, 20.0f};
        transform2.Prepend(transform3);
        transform3 = Transform{triangle.CenterOfGravity()};
        transform2.Append(transform3);
        Transform<float> transform{Transform<float>::InitAsInverse, transform2};
        ThreePoints transformedTriangle;
        for (int i = 0; i < 3; ++i) {
            Vector<float> point = triangle[i];
            transform.ApplyTo(point);
            transformedTriangle[i] = point;
        }

        BoundingBox<float> box;
        for (int i = 0; i < 3; ++i) {
            box.Grow(transformedTriangle[i]);
        }
        int minX { static_cast<int>(box.MinCorner().x / maxDistance) - 1 };
        int maxX { static_cast<int>(box.MaxCorner().x / maxDistance) + 1 };
        int minY { static_cast<int>(box.MinCorner().y / maxDistance) - 1 };
        int maxY { static_cast<int>(box.MaxCorner().y / maxDistance) + 1 };
        Vector<float> direction{0.0f, 0.0f, 1.0f};
        Vector<float> intersectionPoint;
        for (int y = minY; y <= maxY; ++y) {
            for (int x = minX; x <= maxX; ++x) {
                Vector<float> position{static_cast<float>(x) * maxDistance, static_cast<float>(y) * maxDistance, -2.0f};
                bool          intersects;
                Vector<float> intersectionPoint;
                if (LineTriangleIntersection::Compute(position, direction, transformedTriangle, intersects,
                                                      intersectionPoint)) {
                    transform2.ApplyTo(intersectionPoint);
                    pointHandler.OnPoint(intersectionPoint);
                }
            }
        }
    }
}

int Tools::IndexMod3(int index) {
    while (index < 0) {
        index += 3;
    }
    while (index >= 3) {
        index -= 3;
    }
    return index;
}

int Tools::IndexMod2(int index) {
    while (index < 0) {
        index += 2;
    }
    while (index >= 2) {
        index -= 2;
    }
    return index;
}

}    // Namespace Core.
}    // Namespace Vectoid.
