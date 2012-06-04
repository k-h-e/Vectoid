//
//  Range.h
//  kxm
//
//  Created by Kai Hergenroether on 5/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_VECTOID_RANGE_H_
#define KXM_VECTOID_RANGE_H_


namespace kxm {
namespace Vectoid {

//! Range (closed interval) of real numbers (represented by <c>float</c>s).
/*!
 *  \ingroup Vectoid
 */
class Range {
  public:
    Range(float first);
    Range(float number, float anotherNumber);
    //! Creates a range of the same interval as the specified other range, but offsets it as
    //! specified.
    Range(const Range &other, float offset);
    // Instances may get copied.
    
    //! Grows the range (if necessary) so that it includes the specified number.
    void Grow(float number);
    //! Clamps the specified number to the range.
    inline void Clamp(float *number) const;
    //! Considers <c>[min, max)</c> as a range where modulo-like arithmetic is done upon, and sets
    //! the specified number <c>n</c> - potentially lying outside that range - to the representative
    //! <c>n'</c> of its equivalence class, with <c>n'</c> in <c>[min, max)</c>. Note that the range
    //! instance represents <c>[min, max]</c> (as opposed to <c>[min, max)</c>).
    /*!
     *  Due to its optimization, the method only works efficiently if the specified number does not
     *  lie farther ouside the range than <c>max - min</c>.
     */
    inline void ClampModulo(float *number) const;
    //! Interprets both numbers as "modulo-clamped" (see ClampModulo() ), determines the specified
    //! number's <c>offset</c> relative to the specified observer inside the ring-like number 
    //! structure <c>[min, max)</c>, and finally updates the number as <c>observer + offset</c>, 
    //! potentially leaving the range <c>[min, max]</c>.
    inline void ExpandModuloForObserver(float observer, float *number) const;
    //! If the range were subdivided into slots of the specified size, the method returns the slot
    //! the specified number would be in, including the resulting remainder. This method does no
    //! bounds checking whatsoever.
    inline void ComputeSlotUnchecked(float number, float slotSize,
                                     int *outSlot, float *outRemainder) const;
    //! Computes the affine combination of the two range delimiters using the given coefficient
    //! <c>t</c> (and <c>(1 - t)</c>).
    inline float AffineCombination(float t) const;
    
  private:
    float min_,
          max_;
};

void Range::Clamp(float *number) const {
    if (*number < min_)
        *number = min_;
    else if (*number > max_)
        *number = max_;
}

void Range::ClampModulo(float *number) const {   
    if (*number < min_) {
        if (min_ == max_) {
            *number = min_;
            return;
        }
        float delta = max_ - min_;
        do {
            *number += delta;
        } while (*number < min_);
        if (*number >= max_)
            *number = min_;
    }
    else if (*number >= max_) {
        if (min_ == max_) {
            *number = min_;
            return;
        }
        float delta = max_ - min_;
        do {
            *number -= delta;
        } while (*number >= max_);
        if (*number < min_)
            *number = min_;
    }
}

void Range::ExpandModuloForObserver(float observer, float *number) const {
    float range = max_ - min_,
          delta = *number - observer;
    if (delta >= 0.0f) {
        if (delta > range/2)
            delta -= range;
    }
    else {
        if (delta < -range/2)
            delta += range;
    }
    *number = observer + delta;
}

void Range::ComputeSlotUnchecked(float number, float slotSize,
                                 int *outSlot, float *outRemainder) const {
    *outSlot      = (number - min_) / slotSize;
    *outRemainder = number - (min_ + (float)*outSlot * slotSize);
}

float Range::AffineCombination(float t) const {
    return (1.0f - t)*min_ + t*max_;
}


}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_RANGE_H_
