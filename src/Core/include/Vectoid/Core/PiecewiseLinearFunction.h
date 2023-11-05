///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_PIECEWISELINEARFUNCTION_H_
#define VECTOID_CORE_PIECEWISELINEARFUNCTION_H_

namespace Vectoid {
namespace Core {

//! Piecewise linear function.
/*!
 *  Template parameter type <c>T</c> must be copyable.
 *
 *  For x values outside the range spanned by the support points, the function evaluates to the y value given by the
 *  respective boundary support point.
 */
template<typename T>
class PiecewiseLinearFunction {
  public:
    PiecewiseLinearFunction()                                                = default;
    PiecewiseLinearFunction(const PiecewiseLinearFunction &other)            = default;
    PiecewiseLinearFunction &operator=(const PiecewiseLinearFunction &other) = default;
    PiecewiseLinearFunction(PiecewiseLinearFunction &&other)                 = default;
    PiecewiseLinearFunction &operator=(PiecewiseLinearFunction &&other)      = default;

    //! Adds the specified support point.
    /*!
     *  The specified support point's <c>x</c> component must be larger than the ones of all previously added support
     *  points. Otherwise the support point will not be added.
     */
    void AddSupportPoint(float x, const T &y);
    //! Evaluates the piecewise linear function for the specified x value.
    T Evaluate(float x) const;

  private:
    struct SupportPoint {
        float x;
        T     y;
        SupportPoint(float anX, const T &aY) : x(anX), y(aY) {}
    };

    std::vector<SupportPoint> supportPoints_;
};

template<typename T>
void PiecewiseLinearFunction<T>::AddSupportPoint(float x, const T &y) {
    if (supportPoints_.size()) {
        if (!(x > supportPoints_[supportPoints_.size() - 1u].x)) {
            return;
        }
    }

    supportPoints_.push_back(SupportPoint(x, y));
}

template<typename T>
T PiecewiseLinearFunction<T>::Evaluate(float x) const {
    if (supportPoints_.size()) {
        int i = 0;
        while (i < static_cast<int>(supportPoints_.size())) {
            const SupportPoint &supportPoint = supportPoints_[i];
            if (x <= supportPoint.x) {
                if (i == 0) {
                    return supportPoint.y;
                } else {
                    const SupportPoint &previousSupportPoint = supportPoints_[i - 1];
                    float t = (x - previousSupportPoint.x) / (supportPoint.x - previousSupportPoint.x);
                    return (1.0f - t)*previousSupportPoint.y + t*supportPoint.y;
                }
            }
            ++i;
        }
        return supportPoints_[i - 1].y;
    } else {
        return T();
    }
}

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_PIECEWISELINEARFUNCTION_H_
