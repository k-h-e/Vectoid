#ifndef KXM_VECTOID_TRANSFORM_H_
#define KXM_VECTOID_TRANSFORM_H_

#include <kxm/Core/NumberTools.h>
#include <kxm/Vectoid/TransformCore.h>
#include <kxm/Vectoid/Vector.h>

namespace kxm {
namespace Vectoid {

//! Indicates one of the three coordinate axes of 3-space.
/*!
 *  Note that we are using a right-hand system and that as such - if we identify the screen
 *  with the <c>xy</c>-plane - the <c>z</c>-axis protudes from the screen.
 */
enum Axis { XAxis, YAxis, ZAxis };

//! 3D transformation limited to rotations and translations - and any combination thereof.
/*! 
 *  \ingroup Vectoid
 */ 
class Transform : public TransformCore {
  public:
    //! To be used with the constructor variant Transform(InitFromOtherMode initMode, const
    //! Transform &other).
    enum InitFromOtherMode { InitAsInverseRotation,
                             InitAsInverseTranslation,
                             InitAsInverse };
    //! Initializes the transform to the identity.
    inline Transform();
    //! Initializes the transform to a translation along the specified vector.
    inline Transform(const Vector &translation);
    //! Initializes the transform to a rotation around one of the coordinate axes.
    inline Transform(Axis axis, float angleDeg);
    //! Initializes the transform to the rotation as given by the (normalized) images of the
    //! coordinate axes under that rotation.
    inline Transform(const Vector &axisImage0, const Vector &axisImage1,
                     const Vector &axisImage2);
    //! Initializes the transform depending on another, using one of various ways to use the
    //! other transform's information.
    inline Transform(InitFromOtherMode initMode, const Transform &other);
    //! Initializes the transform as the matrix product of the two specified other transforms.
    inline Transform(const Transform &left, const Transform &right);
    
    // Default copy, ok.
    
    //! Only updates the transform's translation part as specified.
    inline void SetTranslationPart(const Vector &translation);
    //! Retrieves the transform's translation part.
    inline void GetTranslationPart(Vector *outTranslation) const;
    //! Returns the transform's translation part.
    inline Vector TranslationPart() const;
    //! Only updates the transform's rotation part as given by the (normalized) images of the
    /// coordinate axes under that rotation.
    inline void SetRotationPart(const Vector &axisImage0, const Vector &axisImage1,
                                const Vector &axisImage2);
    //! The transform's rotation part is represented by a <c>3x3</c>-matrix the columns of which
    //! form an orthonormal base of 3-space. This desirable property can deteriorate due to
    //! accumulated roundoff error induced by operations on the transform. This method restores
    //! the orthonormal property. You can call it manually, but it automatically gets invoked
    //! after every <c>AutoReorthonormalizationInterval</c> integrity-threatening operations on
    //! the transform.
    inline void ReorthonormalizeRotationPart();
    /// Transforms the specified vector - or point in 3-space, if we interpret the vector as
    /// point.
    inline void ApplyTo(Vector *v) const;
    //! Replaces the transform by a concatenation of its original value and another transform
    //! such as the other transform is prepended.
    /*!
     *  Prepending the other transform means that it is multiplied to the original transform
     *  from the right. Thus, when the resulting new transform is used to transform a vector,
     *  the other transform is applied first, and the original transform second.
     */
    inline void Prepend(const Transform &other);
    //! Replaces the transform by a concatenation of its original value and another transform
    //! such as the other transform is appended.
    /*!
     *  Appending the other transform means that it is multiplied to the original transform from
     *  the left. Thus, when the resulting new transform is used to transform a vector,
     *  the original transform is applied first, and the other transform second.
     */
    inline void Append(const Transform &other);
    
  private:
    //! After that many multiplications as specified here a transform will get its rotation
    //! part re-orthonormalized in order to compensate for accumulating roundoff error.
    static const int AutoReorthonormalizationInterval = 200;
    
    int multCount_;
};

Transform::Transform() {
    InitAsIdentity();
    multCount_ = 0;
}

Transform::Transform(const Vector &t) {
    matrix_[0][0] = 1.0f;  matrix_[0][1] = 0.0f;  matrix_[0][2] = 0.0f;  matrix_[0][3] = 0.0f;
    matrix_[1][0] = 0.0f;  matrix_[1][1] = 1.0f;  matrix_[1][2] = 0.0f;  matrix_[1][3] = 0.0f;
    matrix_[2][0] = 0.0f;  matrix_[2][1] = 0.0f;  matrix_[2][2] = 1.0f;  matrix_[2][3] = 0.0f;
    matrix_[3][0] = t.x;   matrix_[3][1] = t.y;   matrix_[3][2] = t.z;   matrix_[3][3] = 1.0f;
    multCount_ = 0;
}

Transform::Transform(Axis axis, float angleDeg) {
    float rad = angleDeg / 180.0f * Core::NumberTools::piAsFloat;
    // First, we'll set the rotation part depending on rotation axis...
    switch (axis) {
        case YAxis:
            matrix_[0][0] =  (float)std::cos(rad);
            matrix_[0][1] =                  0.0f;
            matrix_[0][2] = -(float)std::sin(rad);
            
            matrix_[1][0] =                  0.0f;
            matrix_[1][1] =                  1.0f;
            matrix_[1][2] =                  0.0f;
            
            matrix_[2][0] =  (float)std::sin(rad);
            matrix_[2][1] =                  0.0f;
            matrix_[2][2] =  (float)std::cos(rad);
            break;
            
        case ZAxis:
            matrix_[0][0] =  (float)std::cos(rad);
            matrix_[0][1] =  (float)std::sin(rad);
            matrix_[0][2] =                  0.0f;
            
            matrix_[1][0] = -(float)std::sin(rad);
            matrix_[1][1] =  (float)std::cos(rad);
            matrix_[1][2] =                  0.0f;
            
            matrix_[2][0] =                  0.0f;
            matrix_[2][1] =                  0.0f;
            matrix_[2][2] =                  1.0f;
            break;
            
        case XAxis:
        default:
            matrix_[0][0] =                  1.0f;
            matrix_[0][1] =                  0.0f;
            matrix_[0][2] =                  0.0f;
            
            matrix_[1][0] =                  0.0f;
            matrix_[1][1] =  (float)std::cos(rad);
            matrix_[1][2] =  (float)std::sin(rad);
            
            matrix_[2][0] =                  0.0f;
            matrix_[2][1] = -(float)std::sin(rad);
            matrix_[2][2] =  (float)std::cos(rad);
            break;
    }
    // Now init the translation part and the rest...
    matrix_[3][0] = 0.0f;  matrix_[3][1] = 0.0f;  matrix_[3][2] = 0.0f;    // Translation part.
    matrix_[0][3] = 0.0f;  matrix_[1][3] = 0.0f;  matrix_[2][3] = 0.0f;  matrix_[3][3] = 1.0f;
    multCount_ = 0;
}

Transform::Transform(const Vector &axisImage0, const Vector &axisImage1,
                     const Vector &axisImage2) {
    // Set the rotation part as given by the coordinate axis images...
    SetRotationPart(axisImage0, axisImage1, axisImage2);    // Sets multCount_ to 0.      
    // Now init the translation part and the rest...
    matrix_[3][0] = 0.0f;  matrix_[3][1] = 0.0f;  matrix_[3][2] = 0.0f;    // Translation part.
    matrix_[0][3] = 0.0f;  matrix_[1][3] = 0.0f;  matrix_[2][3] = 0.0f;  matrix_[3][3] = 1.0f;
}

Transform::Transform(InitFromOtherMode initMode, const Transform &other) {
    switch (initMode) {
        case InitAsInverseRotation:
            // Set the rotation part (as the transpose of the other transform's rotation part)...
            matrix_[0][0] = other.matrix_[0][0];
            matrix_[1][0] = other.matrix_[0][1];
            matrix_[2][0] = other.matrix_[0][2];
            
            matrix_[0][1] = other.matrix_[1][0];
            matrix_[1][1] = other.matrix_[1][1];
            matrix_[2][1] = other.matrix_[1][2];
            
            matrix_[0][2] = other.matrix_[2][0];
            matrix_[1][2] = other.matrix_[2][1];
            matrix_[2][2] = other.matrix_[2][2];
            
            // Now init the translation part and the rest...
            matrix_[3][0] = 0.0f;  matrix_[3][1] = 0.0f;  matrix_[3][2] = 0.0f;    // Translation.
            matrix_[0][3] = matrix_[1][3] = matrix_[2][3] = 0.0f;  matrix_[3][3] = 1.0f;
            multCount_ = other.multCount_;
            break;
            
        case InitAsInverseTranslation:
            // Set the rotation part to the identity...
            matrix_[0][0] = 1.0f;  matrix_[0][1] = 0.0f;  matrix_[0][2] = 0.0f;
            matrix_[1][0] = 0.0f;  matrix_[1][1] = 1.0f;  matrix_[1][2] = 0.0f;
            matrix_[2][0] = 0.0f;  matrix_[2][1] = 0.0f;  matrix_[2][2] = 1.0f;
            // Now init the translation part and the rest...
            matrix_[3][0] = -other.matrix_[3][0];
            matrix_[3][1] = -other.matrix_[3][1];
            matrix_[3][2] = -other.matrix_[3][2];
            matrix_[0][3] = matrix_[1][3] = matrix_[2][3] = 0.0f;  matrix_[3][3] = 1.0f;
            multCount_ = 0;
            break;
            
        case InitAsInverse:
        default:
            *this = Transform(InitAsInverseTranslation, other);
            Append(Transform(InitAsInverseRotation, other));
            break;
    }
}

Transform::Transform(const Transform &left, const Transform &right) {

    // Remember storage is column-major.

    matrix_[0][0] =   left.matrix_[0][0] * right.matrix_[0][0]
                    + left.matrix_[1][0] * right.matrix_[0][1]
                    + left.matrix_[2][0] * right.matrix_[0][2];
    matrix_[0][1] =   left.matrix_[0][1] * right.matrix_[0][0]
                    + left.matrix_[1][1] * right.matrix_[0][1]
                    + left.matrix_[2][1] * right.matrix_[0][2];
    matrix_[0][2] =   left.matrix_[0][2] * right.matrix_[0][0]
                    + left.matrix_[1][2] * right.matrix_[0][1]
                    + left.matrix_[2][2] * right.matrix_[0][2];
    
    matrix_[1][0] =   left.matrix_[0][0] * right.matrix_[1][0]
                    + left.matrix_[1][0] * right.matrix_[1][1]
                    + left.matrix_[2][0] * right.matrix_[1][2];
    matrix_[1][1] =   left.matrix_[0][1] * right.matrix_[1][0]
                    + left.matrix_[1][1] * right.matrix_[1][1]
                    + left.matrix_[2][1] * right.matrix_[1][2];
    matrix_[1][2] =   left.matrix_[0][2] * right.matrix_[1][0]
                    + left.matrix_[1][2] * right.matrix_[1][1]
                    + left.matrix_[2][2] * right.matrix_[1][2];
    
    matrix_[2][0] =   left.matrix_[0][0] * right.matrix_[2][0]
                    + left.matrix_[1][0] * right.matrix_[2][1]
                    + left.matrix_[2][0] * right.matrix_[2][2];
    matrix_[2][1] =   left.matrix_[0][1] * right.matrix_[2][0]
                    + left.matrix_[1][1] * right.matrix_[2][1]
                    + left.matrix_[2][1] * right.matrix_[2][2];
    matrix_[2][2] =   left.matrix_[0][2] * right.matrix_[2][0]
                    + left.matrix_[1][2] * right.matrix_[2][1]
                    + left.matrix_[2][2] * right.matrix_[2][2];
    
    matrix_[3][0] =   left.matrix_[0][0] * right.matrix_[3][0]
                    + left.matrix_[1][0] * right.matrix_[3][1]
                    + left.matrix_[2][0] * right.matrix_[3][2]
                    + left.matrix_[3][0];
    matrix_[3][1] =   left.matrix_[0][1] * right.matrix_[3][0]
                    + left.matrix_[1][1] * right.matrix_[3][1]
                    + left.matrix_[2][1] * right.matrix_[3][2]
                    + left.matrix_[3][1];
    matrix_[3][2] =   left.matrix_[0][2] * right.matrix_[3][0]
                    + left.matrix_[1][2] * right.matrix_[3][1]
                    + left.matrix_[2][2] * right.matrix_[3][2]
                    + left.matrix_[3][2];
    
    matrix_[0][3] = matrix_[1][3] = matrix_[2][3] = 0.0f;  matrix_[3][3] = 1.0f;
    
    multCount_ = left.multCount_ + right.multCount_ + 1;
    if (multCount_ >= AutoReorthonormalizationInterval)
        ReorthonormalizeRotationPart();
}

void Transform::SetTranslationPart(const Vector &translation) {
    matrix_[3][0] = translation.x;
    matrix_[3][1] = translation.y;
    matrix_[3][2] = translation.z;
}

void Transform::GetTranslationPart(Vector *outTranslation) const {
    outTranslation->x = matrix_[3][0];
    outTranslation->y = matrix_[3][1];
    outTranslation->z = matrix_[3][2];
}

Vector Transform::TranslationPart() const {
    return Vector(matrix_[3][0], matrix_[3][1], matrix_[3][2]);
} 

void Transform::SetRotationPart(const Vector &axisImage0, const Vector &axisImage1,
                                const Vector &axisImage2) {
    matrix_[0][0] = axisImage0.x;  matrix_[0][1] = axisImage0.y;  matrix_[0][2] = axisImage0.z;
    matrix_[1][0] = axisImage1.x;  matrix_[1][1] = axisImage1.y;  matrix_[1][2] = axisImage1.z;
    matrix_[2][0] = axisImage2.x;  matrix_[2][1] = axisImage2.y;  matrix_[2][2] = axisImage2.z;     
    multCount_ = 0;
}

void Transform::ReorthonormalizeRotationPart() {
    Vector column0(matrix_[0][0], matrix_[0][1], matrix_[0][2]),
    column1(matrix_[1][0], matrix_[1][1], matrix_[1][2]),
    column2 = CrossProduct(column0, column1);
    column2.Normalize();
    column0 = CrossProduct(column1, column2);
    column0.Normalize();
    column1 = CrossProduct(column2, column0);
    SetRotationPart(column0, column1, column2);    // Sets multCount_ to 0.
}

void Transform::ApplyTo(Vector *v) const {
    float x = matrix_[0][0]*v->x + matrix_[1][0]*v->y + matrix_[2][0]*v->z + matrix_[3][0],
          y = matrix_[0][1]*v->x + matrix_[1][1]*v->y + matrix_[2][1]*v->z + matrix_[3][1],
          z = matrix_[0][2]*v->x + matrix_[1][2]*v->y + matrix_[2][2]*v->z + matrix_[3][2];
    v->x = x;  v->y = y;  v->z = z;
}

void Transform::Prepend(const Transform &other) {
    Transform result(*this, other);
    *this = result;
}

void Transform::Append(const Transform &other) {
    Transform result(other, *this);
    *this = result;
}
    
}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_TRANSFORM_H_
