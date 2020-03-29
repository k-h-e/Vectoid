#ifndef KXM_VECTOID_COORDSYSINTERFACE_H_
#define KXM_VECTOID_COORDSYSINTERFACE_H_

#include <kxm/Vectoid/HasTransformInterface.h>
#include <kxm/Vectoid/Vector.h>

namespace kxm {
namespace Vectoid {

template<typename T> class Transform;

//! Interface to entities that establish their own local coordinate system specified via a transform relative to some
//! parent coordinate system. This transform can be be modified to move or rotate the entity relative to the parent
//! coordinate system.
/*! 
 *  \ingroup Vectoid
 */ 
class CoordSysInterface : public virtual HasTransformInterface {
  public:
    //! Maps to \ref Transform::Prepend() of the local transform.
    virtual void PrependTransform(const Transform<float> &other) = 0;
    //! Maps to \ref Transform::Append() of the local transform.
    virtual void AppendTransform(const Transform<float> &other) = 0;
    //! Sets the local transform as specified.
    virtual void SetTransform(const Transform<float> &other) = 0;
    // GetTransform() is part of the HasTransformInterface.
    //! Updates the translation part of the local transform as specified.
    virtual void SetPosition(const Vector<float> &pos) = 0;
    //! Retrieves the translation part of the local transform.
    virtual void GetPosition(Vector<float> *outPos) = 0;
    //! Returns the translation part of the local transform.
    virtual Vector<float> Position() = 0;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_COORDSYSINTERFACE_H_
