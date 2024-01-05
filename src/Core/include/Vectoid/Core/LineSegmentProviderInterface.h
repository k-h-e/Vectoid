///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//                                            //     //   //      //  //      //  //     //      //  //     //     //
//    (C) Copyright Kai Hergenröther         //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_LINESEGMENTPROVIDERINTERFACE_H_
#define VECTOID_CORE_LINESEGMENTPROVIDERINTERFACE_H_

#include <K/Core/Interface.h>

namespace Vectoid {
namespace Core {

template<typename T> class Vector;
class TwoPoints;

//! Interface to entities iteratively providing line segments.
class LineSegmentProviderInterface : public virtual K::Core::Interface {
  public:
    //! Tells the provider to (re)start providing line segments from the beginning.
    virtual void PrepareToProvideLineSegments() = 0;
    //! Provides the next line segment vertex data.
    /*!
     *  \return
     *  <c>false</c> in case there are no more line segments. The output parameter is then undefined, and
     *  <c>LineSegmentError()</c> should be checked.
     */
    virtual bool ProvideNextLineSegment(TwoPoints *outLineSegment) = 0;
    //! Tells whether or not the last line segment readout ended because of an error.
    virtual bool LineSegmentError() = 0;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_LINESEGMENTPROVIDERINTERFACE_H_
