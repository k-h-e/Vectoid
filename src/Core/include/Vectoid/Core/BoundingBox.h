#ifndef VECTOID_CORE_BOUNDINGBOX_H_
#define VECTOID_CORE_BOUNDINGBOX_H_

#include <Vectoid/Core/Range.h>

#include <Vectoid/Core/Vector.h>

namespace Vectoid {
namespace Core {

template<typename T> class Vector;

//! Bounding box in 3-space.
template<typename T>
class BoundingBox {
  public:
    //! Creates an undefined bounding box.
    /*!
     *  The bounding box will behave as <c>(0, 0, 0)</c> until \ref Grow() is called the first time. Then, it will no
     *  longer be undefined, but initialized to <c>(number, number, number)</c>, with <c>number</c> being the argument
     *  to the call to \ref Grow().
     */
    BoundingBox() {}
    // Instances may get copied/moved depending on T.

    //! If necessary, grows the bounding box to include the specified point.
    void Grow(const Vector<T> &point) {
        xRange_.Grow(point.x);
        yRange_.Grow(point.y);
        zRange_.Grow(point.z);
    }
    //! Expands the bounding box at each side by the specified length.
    void Expand(T length) {
        xRange_.Expand(length);
        yRange_.Expand(length);
        zRange_.Expand(length);
    }
    //! Scales the bounding box by the specified scaling factor.
    void Scale(T scalingFactor) {
        xRange_.Scale(scalingFactor);
        yRange_.Scale(scalingFactor);
        zRange_.Scale(scalingFactor);
    }
    //! Tells wether the bounding box contains the specified point.
    bool Contains(const Vector<T> &point) const {
        return xRange_.Contains(point.x) && yRange_.Contains(point.y) && zRange_.Contains(point.z);
    }
    //! Returns the bounding box's center.
    Vector<T> Center() const {
        return Vector<T>(xRange_.Center(), yRange_.Center(), zRange_.Center());
    }
    //! Returns the bounding box's extents.
    Vector<T> Extents() const {
        return Vector<T>(xRange_.Extent(), yRange_.Extent(), zRange_.Extent());
    }
    
  private:
    Range<T> xRange_;
    Range<T> yRange_;
    Range<T> zRange_;
};

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_BOUNDINGBOX_H_
