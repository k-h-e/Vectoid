#ifndef KXM_VECTOID_COORDSYSINTERFACE_H_
#define KXM_VECTOID_COORDSYSINTERFACE_H_

#include <kxm/Vectoid/HasTransformInterface.h>
#include <kxm/Vectoid/Vector.h>

namespace kxm {
namespace Vectoid {

class Transform;

//! Interface to entities that establish their own local coordinate system specified via a transform relative to some
//! parent coordinate system. This transform can be be modified to move or rotate the entity relative to the parent
//! coordinate system.
/*! 
 *  \ingroup Vectoid
 */ 
class CoordSysInterface : public virtual HasTransformInterface {
  public:
    //! Maps to \ref Transform::Prepend() of the local transform.
    virtual void PrependTransform(const Transform &other) = 0;
    //! Maps to \ref Transform::Append() of the local transform.
    virtual void AppendTransform(const Transform &other) = 0;
    //! Sets the local transform as specified.
    virtual void SetTransform(const Transform &other) = 0;
    // GetTransform() is part of the HasTransformInterface.
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
