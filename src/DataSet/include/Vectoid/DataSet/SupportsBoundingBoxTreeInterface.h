///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_DATASET_SUPPORTSBOUNDINGBOXTREEINTERFACE_H_
#define VECTOID_DATASET_SUPPORTSBOUNDINGBOXTREEINTERFACE_H_

#include <K/Core/Interface.h>

namespace Vectoid {

namespace Core {
    template<typename T> class BoundingBox;
    template<typename T> class Vector;
}

namespace DataSet {

struct ItemIntersection;

//! Interface to item collections supporting axis-aligned bounding box trees.
class SupportsBoundingBoxTreeInterface : public virtual K::Core::Interface {
  public:
    //! Tells the number of items in the collection.
    virtual int Size() const = 0;
    //! Retrieves the axis-aligned bounding box for the specified item.
    virtual void GetItemBoundingBox(int item, Core::BoundingBox<float> *outBoundingBox) const = 0;
    //! Computes the intersection between the specified line and the specified collection item.
    /*!
     *  \param outIntersection
     *  Will only be valid in case the computation was successful and an intersection has been found.
     *
     *  \return <c>false</c> in case the computation failed. The output parameters will then be undefined.
     */
    virtual bool ComputeLineItemIntersection(
        const Core::Vector<float> &linePoint, const Core::Vector<float> &lineDirection,
        int item, bool *outIntersects, ItemIntersection *outIntersection) = 0;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_DATASET_SUPPORTSBOUNDINGBOXTREEINTERFACE_H_
