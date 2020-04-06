#ifndef VECTOID_CORE_RANGE_H_
#define VECTOID_CORE_RANGE_H_

#include <K/Core/NumberTools.h>

using K::Core::NumberTools;

namespace Vectoid {
namespace Core {

//! Range (closed interval) of real numbers.
/*!
 *  \ingroup Vectoid
 */
template<typename T>
class Range {
  public:
    //! Creates an undefined range.
    /*!
     *  The range will behave as <c>[0, 0]</c> until \ref Grow() is called the first time. Then, it will no longer be
     *  undefined, but initialized to <c>[number, number]</c>, with <c>number</c> being the argument to the call to
     *  \ref Grow().
     */
    Range();
    //! Initializes the range to <c>[first, first]</c>.
    Range(T first);
    //! Initializes the range to the smallest range including both the specified numbers.
    Range(T number, T anotherNumber);
    //! Creates a range of the same interval as the specified other range, but offsets it as specified.
    Range(const Range<T> &other, T offset);
    // Instances may get copied/moved depending on T.
    
    //! Grows the range (if necessary) so that it includes the specified number.
    void Grow(T number);
    //! Expands the range at each side by the specified value.
    void Expand(T value);
    //! Scales the range by the specified scaling factor.
    void Scale(T scalingFactor);
    //! Tells wether the range contains the specified number.
    bool Contains(T number) const;
    //! Clamps the specified number to the range.
    void Clamp(T *number) const;
    //! Considers <c>[min, max)</c> as a range where modulo-like arithmetic is done upon, and sets the specified number
    //! <c>n</c> - potentially lying outside that range - to the representative <c>n'</c> of its equivalence class, with
    //! <c>n'</c> in <c>[min, max)</c>. Note that the range instance represents <c>[min, max]</c> (as opposed to
    //! <c>[min, max)</c>).
    /*!
     *  Due to its optimization, the method only works efficiently if the specified number does not lie farther ouside
     *  the range than <c>max - min</c>.
     */
    void ClampModulo(T *number) const;
    //! Interprets both numbers as "modulo-clamped" (see ClampModulo() ), and puts the specified number "on the right"
    //! side of the specified observer with respect to the shorter distance, potentially making the number leave the
    //! range <c>[min, max]</c>.
    void CorrectForObserver(T *inOutNumber, T observer) const;
    //! If the range were subdivided into slots of the specified size, the method returns the slot the specified number
    //! would be in, including the resulting remainder. This method does no bounds checking whatsoever.
    void ComputeSlotUnchecked(T number, T slotSize,
                                     int *outSlot, T *outRemainder) const;
    //! Computes the affine combination of the two range delimiters using the given coefficient <c>t</c> (and
    //! <c>(1 - t)</c>).
    T AffineCombination(T t) const;
    //! Returns the range's center.
    T Center() const;
    //! Returns the range's extent.
    T Extent() const;
    
  private:
    T    min_;
    T    max_;
    bool undefined_;
};

template<typename T>
Range<T>::Range()
        : min_(0.0f),
          max_(0.0f),
          undefined_(true) {
    // Nop.
}

template<typename T>
Range<T>::Range(T first)
        : min_(first),
          max_(first),
          undefined_(false) {
    // Nop.
}

template<typename T>
Range<T>::Range(T number, T anotherNumber)
        : undefined_(false) {
    if (number < anotherNumber) {
        min_ = number;
        max_ = anotherNumber;
    }
    else {
        min_ = anotherNumber;
        max_ = number;
    }
}

template<typename T>
Range<T>::Range(const Range<T> &other, T offset)
        : undefined_(false) {
    min_ = other.min_ + offset;
    max_ = other.max_ + offset;
}

template<typename T>
void Range<T>::Grow(T number) {
    if (undefined_) {
        min_       = number;
        max_       = number;
        undefined_ = false;
    }
    else {
        if (number < min_) {
            min_ = number;
        }
        else if (number > max_) {
            max_ = number;
        }
    }
}

template<typename T>
void Range<T>::Expand(T value) {
    T center        = Center();
    T newHalfExtent = (T)0.5*Extent() + value;
    NumberTools::ClampMin(&newHalfExtent, (T)0.0f);
    min_ = center - newHalfExtent;
    max_ = center + newHalfExtent;
}

template<typename T>
void Range<T>::Scale(T scalingFactor) {
    T center        = Center();
    T newHalfExtent = scalingFactor * (T)0.5 * Extent();
    min_ = center - newHalfExtent;
    max_ = center + newHalfExtent;
}

template<typename T>
bool Range<T>::Contains(T number) const {
    return (number >= min_) && (number <= max_);
}

template<typename T>
void Range<T>::Clamp(T *number) const {
    if (*number < min_) {
        *number = min_;
    }
    else if (*number > max_) {
        *number = max_;
    }
}

template<typename T>
void Range<T>::ClampModulo(T *number) const {
    if (*number < min_) {
        if (min_ == max_) {
            *number = min_;
            return;
        }
        T delta = max_ - min_;
        do {
            *number += delta;
        } while (*number < min_);
        if (*number >= max_) {
            *number = min_;
        }
    }
    else if (*number >= max_) {
        if (min_ == max_) {
            *number = min_;
            return;
        }
        T delta = max_ - min_;
        do {
            *number -= delta;
        } while (*number >= max_);
        if (*number < min_) {
            *number = min_;
        }
    }
}

template<typename T>
void Range<T>::CorrectForObserver(T *inOutNumber, T observer) const {
    T range = max_ - min_;
    T delta = *inOutNumber - observer;
    if (delta >= 0.0f) {
        if (delta > range/2.0f) {
            delta -= range;
        }
    }
    else {
        if (delta < -range/2.0f) {
            delta += range;
        }
    }
    *inOutNumber = observer + delta;
}

template<typename T>
void Range<T>::ComputeSlotUnchecked(T number, T slotSize, int *outSlot, T *outRemainder) const {
    *outSlot      = (number - min_) / slotSize;
    *outRemainder = number - (min_ + (T)*outSlot * slotSize);
}

template<typename T>
T Range<T>::AffineCombination(T t) const {
    return (1.0f - t)*min_ + t*max_;
}

template<typename T>
T Range<T>::Center() const {
    return (T).5*min_ + (T).5*max_;
}

template<typename T>
T Range<T>::Extent() const {
    return max_ - min_;
}

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_RANGE_H_
