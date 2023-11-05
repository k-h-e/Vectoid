///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//    All rights reserved.                   //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_TRANSFORM_H_
#define VECTOID_CORE_TRANSFORM_H_

#include <K/Core/NumberTools.h>
#include <Vectoid/Core/TransformCore.h>
#include <Vectoid/Core/Vector.h>

namespace Vectoid {
namespace Core {

//! Indicates one of the three coordinate axes of 3-space.
/*!
 *  Note that we are using a right-hand system and that as such - if we identify the screen with the <c>xy</c>-plane -
 *  the <c>z</c>-axis protudes from the screen.
 */
enum class Axis { X, Y, Z };

//! 3D transformation limited to rotations and translations - and any combination thereof.
template<typename T>
class Transform : public TransformCore<T> {
  public:
    //! To be used with the constructor variant <c>Transform(InitFromOtherMode initMode, const Transform &other)</c>.
    enum InitFromOtherMode { InitAsInverseRotation,
                             InitAsInverseTranslation,
                             InitAsInverse };
    //! Initializes the transform to the identity.
    inline Transform();
    //! Initializes the transform to a translation along the specified vector.
    inline Transform(const Vector<T> &translation);
    //! Initializes the transform to a rotation around one of the coordinate axes.
    inline Transform(Axis axis, T angleDeg);
    //! Initializes the transform to the rotation as given by the (normalized) images of the coordinate axes under that
    //! rotation.
    inline Transform(const Vector<T> &axisImage0, const Vector<T> &axisImage1, const Vector<T> &axisImage2);
    //! Initializes the transform depending on another, using one of various ways to use the other transform's
    //! information.
    inline Transform(InitFromOtherMode initMode, const Transform<T> &other);
    //! Initializes the transform as the matrix product of the two specified other transforms.
    inline Transform(const Transform<T> &left, const Transform<T> &right);
    
    // Default copy, ok.
    
    //! Only updates the transform's translation part as specified.
    inline void SetTranslationPart(const Vector<T> &translation);
    //! Retrieves the transform's translation part.
    inline void GetTranslationPart(Vector<T> *outTranslation) const;
    //! Returns the transform's translation part.
    inline Vector<T> TranslationPart() const;
    //! Only updates the transform's rotation part as given by the (normalized) images of the coordinate axes under that
    //! rotation.
    inline void SetRotationPart(const Vector<T> &axisImage0, const Vector<T> &axisImage1, const Vector<T> &axisImage2);
    //! The transform's rotation part is represented by a <c>3x3</c>-matrix the columns of which form an orthonormal
    //! base of 3-space. This desirable property can deteriorate due to accumulated roundoff error induced by operations
    //! on the transform. This method restores the orthonormal property. You can call it manually, but it automatically
    //! gets invoked after every <c>AutoReorthonormalizationInterval</c> integrity-threatening operations on the
    //! transform.
    inline void ReorthonormalizeRotationPart();
    /// Transforms the specified vector - or point in 3-space, if we interpret the vector as point.
    inline void ApplyTo(Vector<T> *v) const;
    //! Replaces the transform by a concatenation of its original value and another transform such as the other
    //! transform is prepended.
    /*!
     *  Prepending the other transform means that it is multiplied to the original transform from the right. Thus, when
     *  the resulting new transform is used to transform a vector, the other transform is applied first, and the
     *  original transform second.
     */
    inline void Prepend(const Transform<T> &other);
    //! Replaces the transform by a concatenation of its original value and another transform such as the other
    //! transform is appended.
    /*!
     *  Appending the other transform means that it is multiplied to the original transform from the left. Thus, when
     *  the resulting new transform is used to transform a vector, the original transform is applied first, and the
     *  other transform second.
     */
    inline void Append(const Transform<T> &other);
    
  private:
    //! After that many multiplications as specified here a transform will get its rotation part re-orthonormalized in
    //!  order to compensate for accumulating roundoff error.
    static const int autoReorthonormalizationInterval = 200;
    
    int multCount_;
};

template<typename T>
Transform<T>::Transform() {
    this->InitAsIdentity();
    multCount_ = 0;
}

template<typename T>
Transform<T>::Transform(const Vector<T> &t) {
    this->matrix_[0][0] = 1.0f;
    this->matrix_[0][1] = 0.0f;
    this->matrix_[0][2] = 0.0f;
    this->matrix_[0][3] = 0.0f;

    this->matrix_[1][0] = 0.0f;
    this->matrix_[1][1] = 1.0f;
    this->matrix_[1][2] = 0.0f;
    this->matrix_[1][3] = 0.0f;

    this->matrix_[2][0] = 0.0f;
    this->matrix_[2][1] = 0.0f;
    this->matrix_[2][2] = 1.0f;
    this->matrix_[2][3] = 0.0f;

    this->matrix_[3][0] = t.x;
    this->matrix_[3][1] = t.y;
    this->matrix_[3][2] = t.z;
    this->matrix_[3][3] = 1.0f;

    multCount_ = 0;
}

template<typename T>
Transform<T>::Transform(Axis axis, T angleDeg) {
    T angleRad = angleDeg / (T)180.0 * (T)K::Core::NumberTools::pi;

    // Set rotation part depending on rotation axis...
    switch (axis) {
        case Axis::Y:
            this->matrix_[0][0] =  std::cos(angleRad);
            this->matrix_[0][1] =                0.0f;
            this->matrix_[0][2] = -std::sin(angleRad);
            
            this->matrix_[1][0] =                0.0f;
            this->matrix_[1][1] =                1.0f;
            this->matrix_[1][2] =                0.0f;
            
            this->matrix_[2][0] =  std::sin(angleRad);
            this->matrix_[2][1] =                0.0f;
            this->matrix_[2][2] =  std::cos(angleRad);
            break;
            
    case Axis::Z:
            this->matrix_[0][0] =  std::cos(angleRad);
            this->matrix_[0][1] =  std::sin(angleRad);
            this->matrix_[0][2] =                0.0f;
            
            this->matrix_[1][0] = -std::sin(angleRad);
            this->matrix_[1][1] =  std::cos(angleRad);
            this->matrix_[1][2] =                0.0f;
            
            this->matrix_[2][0] =                0.0f;
            this->matrix_[2][1] =                0.0f;
            this->matrix_[2][2] =                1.0f;
            break;
            
    case Axis::X:
        default:
            this->matrix_[0][0] =                1.0f;
            this->matrix_[0][1] =                0.0f;
            this->matrix_[0][2] =                0.0f;
            
            this->matrix_[1][0] =                0.0f;
            this->matrix_[1][1] =  std::cos(angleRad);
            this->matrix_[1][2] =  std::sin(angleRad);
            
            this->matrix_[2][0] =                0.0f;
            this->matrix_[2][1] = -std::sin(angleRad);
            this->matrix_[2][2] =  std::cos(angleRad);
            break;
    }

    // Init translation part and the rest...
    this->matrix_[3][0] = 0.0f;
    this->matrix_[3][1] = 0.0f;
    this->matrix_[3][2] = 0.0f;

    this->matrix_[0][3] = 0.0f;
    this->matrix_[1][3] = 0.0f;
    this->matrix_[2][3] = 0.0f;
    this->matrix_[3][3] = 1.0f;

    multCount_ = 0;
}

template<typename T>
Transform<T>::Transform(const Vector<T> &axisImage0, const Vector<T> &axisImage1, const Vector<T> &axisImage2) {
    // Set rotation part as given by coordinate axis images...
    SetRotationPart(axisImage0, axisImage1, axisImage2);    // Sets multCount_ to 0.      

    // Init translation part and the rest...
    this->matrix_[3][0] = 0.0f;
    this->matrix_[3][1] = 0.0f;
    this->matrix_[3][2] = 0.0f;

    this->matrix_[0][3] = 0.0f;
    this->matrix_[1][3] = 0.0f;
    this->matrix_[2][3] = 0.0f;
    this->matrix_[3][3] = 1.0f;
}

template<typename T>
Transform<T>::Transform(InitFromOtherMode initMode, const Transform<T> &other) {
    switch (initMode) {
        case InitAsInverseRotation:
            // Set rotation part (as the transpose of the other transform's rotation part)...
            this->matrix_[0][0] = other.matrix_[0][0];
            this->matrix_[1][0] = other.matrix_[0][1];
            this->matrix_[2][0] = other.matrix_[0][2];
            
            this->matrix_[0][1] = other.matrix_[1][0];
            this->matrix_[1][1] = other.matrix_[1][1];
            this->matrix_[2][1] = other.matrix_[1][2];
            
            this->matrix_[0][2] = other.matrix_[2][0];
            this->matrix_[1][2] = other.matrix_[2][1];
            this->matrix_[2][2] = other.matrix_[2][2];
            
            // Init translation part and the rest...
            this->matrix_[3][0] = 0.0f;
            this->matrix_[3][1] = 0.0f;
            this->matrix_[3][2] = 0.0f;

            this->matrix_[0][3] = 0.0f;
            this->matrix_[1][3] = 0.0f;
            this->matrix_[2][3] = 0.0f;
            this->matrix_[3][3] = 1.0f;

            multCount_ = other.multCount_;
            break;
            
        case InitAsInverseTranslation:
            // Set rotation part to identity...
            this->matrix_[0][0] = 1.0f;
            this->matrix_[0][1] = 0.0f;
            this->matrix_[0][2] = 0.0f;

            this->matrix_[1][0] = 0.0f;
            this->matrix_[1][1] = 1.0f;
            this->matrix_[1][2] = 0.0f;

            this->matrix_[2][0] = 0.0f;
            this->matrix_[2][1] = 0.0f;
            this->matrix_[2][2] = 1.0f;

            // Init translation part and the rest...
            this->matrix_[3][0] = -other.matrix_[3][0];
            this->matrix_[3][1] = -other.matrix_[3][1];
            this->matrix_[3][2] = -other.matrix_[3][2];

            this->matrix_[0][3] = 0.0f;
            this-> matrix_[1][3] = 0.0f;
            this->matrix_[2][3] = 0.0f;
            this->matrix_[3][3] = 1.0f;

            multCount_ = 0;
            break;
            
        case InitAsInverse:
        default:
            *this = Transform<T>(InitAsInverseTranslation, other);
            Append(Transform<T>(InitAsInverseRotation, other));
            break;
    }
}

template<typename T>
Transform<T>::Transform(const Transform<T> &left, const Transform<T> &right) {

    // Remember storage is column-major.

    this->matrix_[0][0] =   left.matrix_[0][0] * right.matrix_[0][0]
                          + left.matrix_[1][0] * right.matrix_[0][1]
                          + left.matrix_[2][0] * right.matrix_[0][2];
    this->matrix_[0][1] =   left.matrix_[0][1] * right.matrix_[0][0]
                          + left.matrix_[1][1] * right.matrix_[0][1]
                          + left.matrix_[2][1] * right.matrix_[0][2];
    this->matrix_[0][2] =   left.matrix_[0][2] * right.matrix_[0][0]
                          + left.matrix_[1][2] * right.matrix_[0][1]
                          + left.matrix_[2][2] * right.matrix_[0][2];
    
    this->matrix_[1][0] =   left.matrix_[0][0] * right.matrix_[1][0]
                          + left.matrix_[1][0] * right.matrix_[1][1]
                          + left.matrix_[2][0] * right.matrix_[1][2];
    this->matrix_[1][1] =   left.matrix_[0][1] * right.matrix_[1][0]
                          + left.matrix_[1][1] * right.matrix_[1][1]
                          + left.matrix_[2][1] * right.matrix_[1][2];
    this->matrix_[1][2] =   left.matrix_[0][2] * right.matrix_[1][0]
                          + left.matrix_[1][2] * right.matrix_[1][1]
                          + left.matrix_[2][2] * right.matrix_[1][2];
    
    this->matrix_[2][0] =   left.matrix_[0][0] * right.matrix_[2][0]
                          + left.matrix_[1][0] * right.matrix_[2][1]
                          + left.matrix_[2][0] * right.matrix_[2][2];
    this->matrix_[2][1] =   left.matrix_[0][1] * right.matrix_[2][0]
                          + left.matrix_[1][1] * right.matrix_[2][1]
                          + left.matrix_[2][1] * right.matrix_[2][2];
    this->matrix_[2][2] =   left.matrix_[0][2] * right.matrix_[2][0]
                          + left.matrix_[1][2] * right.matrix_[2][1]
                          + left.matrix_[2][2] * right.matrix_[2][2];
    
    this->matrix_[3][0] =   left.matrix_[0][0] * right.matrix_[3][0]
                          + left.matrix_[1][0] * right.matrix_[3][1]
                          + left.matrix_[2][0] * right.matrix_[3][2]
                          + left.matrix_[3][0];
    this->matrix_[3][1] =   left.matrix_[0][1] * right.matrix_[3][0]
                          + left.matrix_[1][1] * right.matrix_[3][1]
                          + left.matrix_[2][1] * right.matrix_[3][2]
                          + left.matrix_[3][1];
    this->matrix_[3][2] =   left.matrix_[0][2] * right.matrix_[3][0]
                          + left.matrix_[1][2] * right.matrix_[3][1]
                          + left.matrix_[2][2] * right.matrix_[3][2]
                          + left.matrix_[3][2];
    
    this->matrix_[0][3] = 0.0f;
    this->matrix_[1][3] = 0.0f;
    this->matrix_[2][3] = 0.0f;
    this->matrix_[3][3] = 1.0f;
    
    multCount_ = left.multCount_ + right.multCount_ + 1;
    if (multCount_ >= autoReorthonormalizationInterval)
        ReorthonormalizeRotationPart();
}

template<typename T>
void Transform<T>::SetTranslationPart(const Vector<T> &translation) {
    this->matrix_[3][0] = translation.x;
    this->matrix_[3][1] = translation.y;
    this->matrix_[3][2] = translation.z;
}

template<typename T>
void Transform<T>::GetTranslationPart(Vector<T> *outTranslation) const {
    outTranslation->x = this->matrix_[3][0];
    outTranslation->y = this->matrix_[3][1];
    outTranslation->z = this->matrix_[3][2];
}

template<typename T>
Vector<T> Transform<T>::TranslationPart() const {
    return Vector<T>(this->matrix_[3][0], this->matrix_[3][1], this->matrix_[3][2]);
} 

template<typename T>
void Transform<T>::SetRotationPart(const Vector<T> &axisImage0, const Vector<T> &axisImage1,
                                   const Vector<T> &axisImage2) {
    this->matrix_[0][0] = axisImage0.x;
    this->matrix_[0][1] = axisImage0.y;
    this->matrix_[0][2] = axisImage0.z;

    this->matrix_[1][0] = axisImage1.x;
    this->matrix_[1][1] = axisImage1.y;
    this->matrix_[1][2] = axisImage1.z;

    this->matrix_[2][0] = axisImage2.x;
    this->matrix_[2][1] = axisImage2.y;
    this->matrix_[2][2] = axisImage2.z;

    multCount_ = 0;
}

template<typename T>
void Transform<T>::ReorthonormalizeRotationPart() {
    Vector<T> column0(this->matrix_[0][0], this->matrix_[0][1], this->matrix_[0][2]);
    Vector<T> column1(this->matrix_[1][0], this->matrix_[1][1], this->matrix_[1][2]);
    Vector<T> column2 = CrossProduct(column0, column1);
    column2.Normalize();
    column0 = CrossProduct(column1, column2);
    column0.Normalize();
    column1 = CrossProduct(column2, column0);
    SetRotationPart(column0, column1, column2);    // Sets multCount_ to 0.
}

template<typename T>
void Transform<T>::ApplyTo(Vector<T> *v) const {
    T x = this->matrix_[0][0]*v->x + this->matrix_[1][0]*v->y + this->matrix_[2][0]*v->z + this->matrix_[3][0];
    T y = this->matrix_[0][1]*v->x + this->matrix_[1][1]*v->y + this->matrix_[2][1]*v->z + this->matrix_[3][1];
    T z = this->matrix_[0][2]*v->x +this-> matrix_[1][2]*v->y + this->matrix_[2][2]*v->z + this->matrix_[3][2];

    v->x = x;
    v->y = y;
    v->z = z;
}

template<typename T>
void Transform<T>::Prepend(const Transform<T> &other) {
    Transform<T> result(*this, other);
    *this = result;
}

template<typename T>
void Transform<T>::Append(const Transform<T> &other) {
    Transform<T> result(other, *this);
    *this = result;
}
    
}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_TRANSFORM_H_
