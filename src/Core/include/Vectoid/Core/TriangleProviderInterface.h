///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_TRIANGLEPROVIDERINTERFACE_H_
#define VECTOID_CORE_TRIANGLEPROVIDERINTERFACE_H_

#include <K/Core/Interface.h>

namespace Vectoid {
namespace Core {

template<typename T> class Vector;
class ThreePoints;

//! Interface to entities iteratively providing triangles.
class TriangleProviderInterface : public virtual K::Core::Interface {
  public:
    //! Tells the provider to (re)start providing triangles from the beginning.
    virtual void PrepareToProvideTriangles() = 0;
    //! Provides the next triangle vertex data.
    /*!
     *  \return
     *  <c>false</c> in case there are no more triangles. The output parameter is then undefined, and
     *  <c>TriangleError()</c> should be checked.
     */
    virtual bool ProvideNextTriangle(ThreePoints &outTriangle) = 0;
    //! Provides the normal for the current triangle.
    virtual void ProvideNormal(Vector<float> &outNormal) = 0;
    //! Tells whether or not the last triangle readout ended because of an error.
    virtual bool TriangleError() = 0;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_TRIANGLEPROVIDERINTERFACE_H_
