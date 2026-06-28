///////////////////////////////////////////////////////////////////////// ///////////////////      //
//                                                                                                //
//    SonarBot                                                                      //////////// /////////    //      //
//    Distributed System Software                                                 //            //       //    //  //
//    (C) Copyright SonarBot Exploration Services GmbH                            ///////////  //        //     //
//                                                                                         // //       //    //  //
//////////////////////////////////////////////////////////////////////////////  ////////////  /////////   //      //

#ifndef VECTOID_CORE_DEBUGGEOMETRYHANDLERINTERFACE_H_
#define VECTOID_CORE_DEBUGGEOMETRYHANDLERINTERFACE_H_

#include <K/Core/Interface.h>

namespace Vectoid {
    namespace Core {
        class ThreePoints;
        class TwoPoints;
    }
}

namespace Vectoid {
namespace Core {

//! Interface to entities handling debug geometry.
class DebugGeometryHandlerInterface : public virtual K::Core::Interface {
  public:
    //! Informs the handler about a new debug line segment.
    virtual void OnDebugLineSegment(const TwoPoints &segment) = 0;
    //! Informs the handler about a new debug triangle.
    virtual void OnDebugTriangle(const ThreePoints &triangle) = 0;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_DEBUGGEOMETRYHANDLERINTERFACE_H_
