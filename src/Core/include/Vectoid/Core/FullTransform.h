///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_FULLTRANSFORM_H_
#define VECTOID_CORE_FULLTRANSFORM_H_

#include <Vectoid/Core/TransformCore.h>

namespace Vectoid {
namespace Core {

//! Full 3D transform (not limited to rotations, translations and combinations thereof, as is <c>Transform</c>).
class FullTransform : public TransformCore<float> {
  public:
    //! Initializes the transform to the identity.
    inline FullTransform();
    //! Initializes the transform as the matrix product of the two specified other transforms.
    inline FullTransform(const TransformCore<float> &left, const TransformCore<float> &right);
    // Default copy, ok.
    
    //! Sets up a perspective projection.
    inline void SetFrustum(float left, float right, float bottom, float top, float zNear, float zFar);
    //! Allows direct access to the specified matrix element.
    inline float &Element(int row, int column);
};

FullTransform::FullTransform() {
    InitAsIdentity();
}

FullTransform::FullTransform(const TransformCore<float> &left, const TransformCore<float> &right) {
    
    // Remember storage is column-major.

    matrix_[0][0] =   left.matrix_[0][0] * right.matrix_[0][0]
                    + left.matrix_[1][0] * right.matrix_[0][1]
                    + left.matrix_[2][0] * right.matrix_[0][2]
                    + left.matrix_[3][0] * right.matrix_[0][3];
    matrix_[0][1] =   left.matrix_[0][1] * right.matrix_[0][0]
                    + left.matrix_[1][1] * right.matrix_[0][1]
                    + left.matrix_[2][1] * right.matrix_[0][2]
                    + left.matrix_[3][1] * right.matrix_[0][3];
    matrix_[0][2] =   left.matrix_[0][2] * right.matrix_[0][0]
                    + left.matrix_[1][2] * right.matrix_[0][1]
                    + left.matrix_[2][2] * right.matrix_[0][2]
                    + left.matrix_[3][2] * right.matrix_[0][3];
    matrix_[0][3] =   left.matrix_[0][3] * right.matrix_[0][0]
                    + left.matrix_[1][3] * right.matrix_[0][1]
                    + left.matrix_[2][3] * right.matrix_[0][2]
                    + left.matrix_[3][3] * right.matrix_[0][3];
    
    matrix_[1][0] =   left.matrix_[0][0] * right.matrix_[1][0]
                    + left.matrix_[1][0] * right.matrix_[1][1]
                    + left.matrix_[2][0] * right.matrix_[1][2]
                    + left.matrix_[3][0] * right.matrix_[1][3];
    matrix_[1][1] =   left.matrix_[0][1] * right.matrix_[1][0]
                    + left.matrix_[1][1] * right.matrix_[1][1]
                    + left.matrix_[2][1] * right.matrix_[1][2]
                    + left.matrix_[3][1] * right.matrix_[1][3];
    matrix_[1][2] =   left.matrix_[0][2] * right.matrix_[1][0]
                    + left.matrix_[1][2] * right.matrix_[1][1]
                    + left.matrix_[2][2] * right.matrix_[1][2]
                    + left.matrix_[3][2] * right.matrix_[1][3];
    matrix_[1][3] =   left.matrix_[0][3] * right.matrix_[1][0]
                    + left.matrix_[1][3] * right.matrix_[1][1]
                    + left.matrix_[2][3] * right.matrix_[1][2]
                    + left.matrix_[3][3] * right.matrix_[1][3];
                    
    matrix_[2][0] =   left.matrix_[0][0] * right.matrix_[2][0]
                    + left.matrix_[1][0] * right.matrix_[2][1]
                    + left.matrix_[2][0] * right.matrix_[2][2]
                    + left.matrix_[3][0] * right.matrix_[2][3];
    matrix_[2][1] =   left.matrix_[0][1] * right.matrix_[2][0]
                    + left.matrix_[1][1] * right.matrix_[2][1]
                    + left.matrix_[2][1] * right.matrix_[2][2]
                    + left.matrix_[3][1] * right.matrix_[2][3];
    matrix_[2][2] =   left.matrix_[0][2] * right.matrix_[2][0]
                    + left.matrix_[1][2] * right.matrix_[2][1]
                    + left.matrix_[2][2] * right.matrix_[2][2]
                    + left.matrix_[3][2] * right.matrix_[2][3];
    matrix_[2][3] =   left.matrix_[0][3] * right.matrix_[2][0]
                    + left.matrix_[1][3] * right.matrix_[2][1]
                    + left.matrix_[2][3] * right.matrix_[2][2]
                    + left.matrix_[3][3] * right.matrix_[2][3];
                    
    matrix_[3][0] =   left.matrix_[0][0] * right.matrix_[3][0]
                    + left.matrix_[1][0] * right.matrix_[3][1]
                    + left.matrix_[2][0] * right.matrix_[3][2]
                    + left.matrix_[3][0] * right.matrix_[3][3];
    matrix_[3][1] =   left.matrix_[0][1] * right.matrix_[3][0]
                    + left.matrix_[1][1] * right.matrix_[3][1]
                    + left.matrix_[2][1] * right.matrix_[3][2]
                    + left.matrix_[3][1] * right.matrix_[3][3];
    matrix_[3][2] =   left.matrix_[0][2] * right.matrix_[3][0]
                    + left.matrix_[1][2] * right.matrix_[3][1]
                    + left.matrix_[2][2] * right.matrix_[3][2]
                    + left.matrix_[3][2] * right.matrix_[3][3];
    matrix_[3][3] =   left.matrix_[0][3] * right.matrix_[3][0]
                    + left.matrix_[1][3] * right.matrix_[3][1]
                    + left.matrix_[2][3] * right.matrix_[3][2]
                    + left.matrix_[3][3] * right.matrix_[3][3];
}

float &FullTransform::Element(int row, int column) {
    return matrix_[column][row];    // Storage is column-major.
}

void FullTransform::SetFrustum(float left, float right, float bottom, float top, float zNear, float zFar) {

    // Storage is column-major.
    
    matrix_[0][0] =  2.0f * zNear / (right - left);
    matrix_[0][1] =  0.0f;
    matrix_[0][2] =  0.0f;
    matrix_[0][3] =  0.0f;
    
    matrix_[1][0] =  0.0f;
    matrix_[1][1] =  2.0f * zNear / (top - bottom);
    matrix_[1][2] =  0.0f;
    matrix_[1][3] =  0.0f;
    
    matrix_[2][0] =  (right + left) / (right - left);
    matrix_[2][1] =  (top + bottom) / (top - bottom);
    matrix_[2][2] = -(zFar + zNear) / (zFar - zNear);
    matrix_[2][3] = -1.0f;
    
    matrix_[3][0] =  0.0f;
    matrix_[3][1] =  0.0f;
    matrix_[3][2] =  -(2.0f * zFar * zNear) / (zFar - zNear);
    matrix_[3][3] =  0.0f;
}

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_FULLTRANSFORM_H_

