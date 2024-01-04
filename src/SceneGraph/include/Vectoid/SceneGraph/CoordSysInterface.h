///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_SCENEGRAPH_COORDSYSINTERFACE_H_
#define VECTOID_SCENEGRAPH_COORDSYSINTERFACE_H_

#include <Vectoid/Core/HasTransformInterface.h>
#include <Vectoid/Core/Vector.h>

namespace Vectoid {
namespace Core {
    template<typename T> class Transform;
}
}

namespace Vectoid {
namespace SceneGraph {

//! Interface to entities that establish their own local coordinate system specified via a transform relative to some
//! parent coordinate system. This transform can be be modified to move or rotate the entity relative to the parent
//! coordinate system.
class CoordSysInterface : public virtual Core::HasTransformInterface {
  public:
    //! Maps to \ref Transform::Prepend() of the local transform.
    virtual void PrependTransform(const Core::Transform<float> &other) = 0;
    //! Maps to \ref Transform::Append() of the local transform.
    virtual void AppendTransform(const Core::Transform<float> &other) = 0;
    //! Sets the local transform as specified.
    virtual void SetTransform(const Core::Transform<float> &other) = 0;
    // GetTransform() is part of the HasTransformInterface.
    //! Updates the translation part of the local transform as specified.
    virtual void SetPosition(const Core::Vector<float> &pos) = 0;
    //! Retrieves the translation part of the local transform.
    virtual void GetPosition(Core::Vector<float> *outPos) = 0;
    //! Returns the translation part of the local transform.
    virtual Core::Vector<float> Position() = 0;
};

}    // Namespace SceneGraph.
}    // Namespace Vectoid.

#endif    // VECTOID_SCENEGRAPH_COORDSYSINTERFACE_H_
