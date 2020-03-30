#ifndef VECTOID_CORE_HASBOUNDINGBOXINTERFACE_H_
#define VECTOID_CORE_HASBOUNDINGBOXINTERFACE_H_

#include <kxm/Core/Interface.h>

namespace Vectoid {
namespace Core {

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

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_HASBOUNDINGBOXINTERFACE_H_
