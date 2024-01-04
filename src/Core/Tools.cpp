///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/Core/Tools.h>

#include <cmath>
#include <vector>
#include <K/Core/NumberTools.h>
#include <Vectoid/Core/Vector.h>
#include <Vectoid/Core/ThreePoints.h>

using std::atan2;
using std::isfinite;
using std::nullopt;
using std::optional;
using std::vector;
using K::Core::NumberTools;

namespace Vectoid {
namespace Core {

void Tools::CreateCoordinateSystem(const Vector<float> &direction, Vector<float> *outU, Vector<float> *outV) {
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

    *outU = CrossProduct(direction, bestBase);
    outU->Normalize();
    *outV = CrossProduct(direction, *outU);
    outV->Normalize();
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
