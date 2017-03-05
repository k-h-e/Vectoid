#ifndef KXM_VECTOID_HASBOUNDINGBOXINTERFACE_H_
#define KXM_VECTOID_HASBOUNDINGBOXINTERFACE_H_

#include <kxm/Core/Interface.h>

namespace kxm {
namespace Vectoid {

class BoundingBox;

//! Interface to entities having an associated bounding box.
/*! 
 *  \ingroup Vectoid
 */ 
class HasBoundingBoxInterface : public virtual Core::Interface {
  public:
    //! Retrieves the associated bounding box.
    virtual void GetBoundingBox(BoundingBox *outBoundingBox) = 0;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_HASBOUNDINGBOXINTERFACE_H_
