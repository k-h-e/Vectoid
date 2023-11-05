///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_ITEMINTERSECTION_H_
#define VECTOID_DATASET_ITEMINTERSECTION_H_

#include <Vectoid/Core/Vector.h>

namespace Vectoid {
namespace DataSet {

//! Holds information describing an intersection between an item and another geometric primitive.
/*!
 *  The contents must be interpreted according to context.
 */
struct ItemIntersection {
    int                 item;
    Core::Vector<float> point;

    ItemIntersection() : item(-1) {}
    ItemIntersection(int anItem, const Core::Vector<float> &aPoint) : item(anItem), point(aPoint) {}
    ItemIntersection(const ItemIntersection &other)            = default;
    ItemIntersection &operator=(const ItemIntersection &other) = default;
    ItemIntersection(ItemIntersection &&other)                 = default;
    ItemIntersection &operator=(ItemIntersection &&other)      = default;
};

}    // Namespace DataSet.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_ITEMINTERSECTION_H_
