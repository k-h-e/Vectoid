///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#include <Vectoid/DataSet/GeometryTools.h>

#include <K/Core/NumberTools.h>
#include <Vectoid/Core/ThreePoints.h>
#include <Vectoid/Core/Transform.h>
#include <Vectoid/DataSet/SimpleTriangleList.h>

using K::Core::NumberTools;
using Vectoid::Core::Axis;
using Vectoid::Core::ThreePoints;
using Vectoid::Core::Transform;
using Vectoid::Core::Vector;

namespace Vectoid {
namespace DataSet {

void GeometryTools::AddLineXY(SimpleTriangleList *triangleList, const Vector<float> &startPoint,
                              const Vector<float> &endPoint, float width) {
    width = (width > 0.0f) ? width : 1.0f;
    Vector<float> start{startPoint};
    Vector<float> end{endPoint};
    start.z = 0.0f;
    end.z = 0.0f;
    Vector<float> direction{end - start};
    direction.Normalize();
    if (direction.Valid()) {
        Vector<float> normal{-direction.y, direction.x, 0.0f};
        triangleList->Add(ThreePoints{start + .5f*width*normal, start - .5f*width*normal, end - .5f*width*normal});
        triangleList->Add(ThreePoints{start + .5f*width*normal, end - .5f*width*normal, end + .5f*width*normal});
    }
}

void GeometryTools::AddFilledCircleXY(SimpleTriangleList *triangleList, const Vector<float> &center, float radius,
                                      int numSectors) {
    Vector<float> centerXY{center};
    centerXY.z = 0.0f;
    radius = (radius > 0.0f) ? radius : 1.0f;
    NumberTools::ClampMin(&numSectors, 3);
    Vector<float> firstHand;
    Vector<float> oldHand;
    for (int i = 0; i < numSectors; ++i) {
        float angle{(static_cast<float>(i)/static_cast<float>(numSectors)) * 360.0f};
        Transform<float> rotation{Axis::Z, angle};
        Vector<float> hand{radius, 0.0f, 0.0f};
        rotation.ApplyTo(&hand);
        if (i) {
            triangleList->Add(ThreePoints{centerXY, centerXY + oldHand, centerXY + hand});
        }
        
        oldHand = hand;
        if (!i) {
            firstHand = hand;
        }
    }
    
    triangleList->Add(ThreePoints{centerXY, centerXY + oldHand, centerXY + firstHand});
}

void GeometryTools::AddFilledCircleSectorXY(SimpleTriangleList *triangleList, float radius, float centerAngle,
                                            float openingAngle, int numSubdivisions) {
    radius = (radius > 0.0f) ? radius : 1.0f;
    NumberTools::Clamp(&centerAngle, 0.0f, 360.0f);
    openingAngle = (openingAngle > 0.0f) ? openingAngle : 1.0f;
    openingAngle = (openingAngle < 360.0f) ? openingAngle : 359.0f;
    NumberTools::ClampMin(&numSubdivisions, 3);
    Vector<float> oldHand;
    for (int i = 0; i <= numSubdivisions; ++i) {
         float t = static_cast<float>(i) / static_cast<float>(numSubdivisions);
         NumberTools::Clamp(&t, 0.0f, 1.0f);
         float angle = (1.0f - t)*(centerAngle - .5f*openingAngle) + t*(centerAngle + .5f*openingAngle);
         if (angle < 0.0f) {
             angle += 360.0f;
         } else if (angle > 360.0f) {
             angle -= 360.0f;
         }
         
         Transform<float> rotation{Axis::Z, angle};
         Vector<float> hand{radius, 0.0f, 0.0f};
         rotation.ApplyTo(&hand);
         if (i) {
            triangleList->Add(ThreePoints{Vector<float>{}, oldHand, hand});
         }
         
         oldHand = hand;
    }
}

void GeometryTools::AddCircleXY(SimpleTriangleList *triangleList, float radius, int numSectors, float width) {
    radius = (radius > 0.0f) ? radius : 1.0f;
    NumberTools::ClampMin(&numSectors, 3);
    width = (width > 0.0f) ? width : .5f*radius;
    width = (width < radius) ? width : .5f*radius;
    Vector<float> firstHand;
    Vector<float> firstInnerHand;
    Vector<float> oldHand;
    Vector<float> oldInnerHand;
    for (int i = 0; i < numSectors; ++i) {
        float angle{(static_cast<float>(i)/static_cast<float>(numSectors)) * 360.0f};
        Transform<float> rotation{Axis::Z, angle};
        Vector<float> hand{radius, 0.0f, 0.0f};
        Vector<float> innerHand{radius - width, 0.0f, 0.0f};
        rotation.ApplyTo(&hand);
        rotation.ApplyTo(&innerHand);
        if (i) {
            triangleList->Add(ThreePoints{oldInnerHand, oldHand, hand});
            triangleList->Add(ThreePoints{oldInnerHand, hand, innerHand});
        }
        
        oldHand      = hand;
        oldInnerHand = innerHand;
        if (!i) {
            firstHand      = hand;
            firstInnerHand = innerHand;
        }
    }
    
    triangleList->Add(ThreePoints{oldInnerHand, oldHand, firstHand});
    triangleList->Add(ThreePoints{oldInnerHand, firstHand, firstInnerHand});
}

}    // Namespace DataSet.
}    // Namespace Vectoid.
