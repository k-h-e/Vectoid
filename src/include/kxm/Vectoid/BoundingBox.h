#ifndef KXM_VECTOID_BOUNDINGBOX_H_
#define KXM_VECTOID_BOUNDINGBOX_H_

#include <kxm/Vectoid/Range.h>

#include <kxm/Vectoid/Vector.h>

namespace kxm {
namespace Vectoid {

class Vector;

//! Bounding box in 3-space.
/*! 
 *  \ingroup Vectoid
 */ 
class BoundingBox {
  public:
    //! Creates an undefined bounding box.
    /*!
     *  The bounding box will behave as <c>(0, 0, 0)</c> until \ref Grow() is called the first time. Then, it will no
     *  longer be undefined, but initialized to <c>(number, number, number)</c>, with <c>number</c> being the argument
     *  to the call to \ref Grow().
     */
    BoundingBox();
    //! If necessary, grows the bounding box to include the specified point.
    void Grow(const Vector &point);
    //! Tells wether the bounding box contains the specified point.
    inline bool Contains(const Vector &point) const;
    
  private:
    Range xRange_,
          yRange_,
          zRange_;
};

bool BoundingBox::Contains(const Vector &point) const {
    return xRange_.Contains(point.x) && yRange_.Contains(point.y) && zRange_.Contains(point.z);
}

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_BOUNDINGBOX_H_
