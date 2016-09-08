//
//  CoordSysInterface.h
//  kxm
//
//  Created by Kai Hergenroether on 4/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef KXM_VECTOID_COORDSYSINTERFACE_H_
#define KXM_VECTOID_COORDSYSINTERFACE_H_


#include <kxm/Core/Interface.h>
#include <Vectoid/Vector.h>


namespace kxm {
namespace Vectoid {

class Transform;

//! Interface to entities that establish their own local coordinate system specified via a
//! transform relative to some parent coordinate system. This transform can be be modified to move
//! or rotate the entity relative to the parent coordinate system.
/*! 
 *  \ingroup Vectoid
 */ 
class CoordSysInterface : public virtual Core::Interface {
  public:
    //! Maps to \ref Transform::Prepend() of the local transform.
    virtual void PrependTransform(const Transform &other) = 0;
    //! Maps to \ref Transform::Append() of the local transform.
    virtual void AppendTransform(const Transform &other) = 0;
    //! Sets the local transform as specified.
    virtual void SetTransform(const Transform &other) = 0;
    //! Retrieves the local transform.
    virtual void GetTransform(Transform *outTransform) const = 0;
    //! Updates the translation part of the local transform as specified.
    virtual void SetPosition(const Vector &pos) = 0;
    //! Retrieves the translation part of the local transform.
    virtual void GetPosition(Vector *outPos) = 0;
    //! Returns the translation part of the local transform.
    virtual Vector Position() = 0;
};

}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_COORDSYSINTERFACE_H_
