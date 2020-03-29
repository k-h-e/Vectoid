#ifndef KXM_VECTOID_BOUNDINGBOX_H_
#define KXM_VECTOID_BOUNDINGBOX_H_

#include <kxm/Vectoid/Range.h>

#include <kxm/Vectoid/Vector.h>

namespace kxm {
namespace Vectoid {

template<typename T> class Vector;

//! Bounding box in 3-space.
/*! 
 *  \ingroup Vectoid
 */
template<typename T>
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
    void Grow(const Vector<T> &point) {
        xRange_.Grow(point.x);
        yRange_.Grow(point.y);
        zRange_.Grow(point.z);
    }
    //! Tells wether the bounding box contains the specified point.
    bool Contains(const Vector<T> &point) const {
        return xRange_.Contains(point.x) && yRange_.Contains(point.y) && zRange_.Contains(point.z);
    }
    
  private:
    Range<T> xRange_;
    Range<T> yRange_;
    Range<T> zRange_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_BOUNDINGBOX_H_
