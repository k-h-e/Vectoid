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
    // Instances may get copied.
    
    //! Grows the range (if necessary) so that it includes the specified number.
    void Grow(float number);
    //! Clamps the specified number to the range.
    void Clamp(float *number);
    //! Considers <c>[min, max)</c> as a range where modulo-like arithmetic is done upon, and sets
    //! the specified number <c>n</c> - potentially lying outside that range - to the representative
    //! <c>n'</c> of its equivalence class, with <c>n'</c> in <c>[min, max)</c>. Note that the range
    //! instance represents <c>[min, max]</c> (as opposed to <c>[min, max)</c>).
    void SetToModuloEquivalent(float *number);
    
  private:
    float min_,
          max_;
};


}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_RANGE_H_
