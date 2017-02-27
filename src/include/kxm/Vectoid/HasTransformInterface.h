#ifndef KXM_VECTOID_HASTRANSFORMINTERFACE_H_
#define KXM_VECTOID_HASTRANSFORMINTERFACE_H_

#include <kxm/Core/Interface.h>

namespace kxm {
namespace Vectoid {

class Transform;

//! Interface to entities having an associated transform, as for example a \ref CoordSys.
/*! 
 *  \ingroup Vectoid
 */ 
class HasTransformInterface : public virtual Core::Interface {
  public:
    //! Retrieves the associated transform.
    virtual void GetTransform(Transform *outTransform) const = 0;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_HASTRANSFORMINTERFACE_H_
