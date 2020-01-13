#ifndef KXM_VECTOID_TRANSFORMCORE_H_
#define KXM_VECTOID_TRANSFORMCORE_H_

#include <kxm/Core/NumberTools.h>
#include <kxm/Vectoid/Vector.h>

namespace kxm {
namespace Vectoid {

//! Base class to 3D transforms.
/*!
 *  \ingroup Vectoid
 */
class TransformCore {
  public:
    // No element initialization during construction, subclasses must do this! Want to avoid duplicate element
    // initializations for performance reasons.
    
    // Default copy, ok.
  
    //! Provides read access to the elements of the encapsuled 4x4 matrix in <c>OpenGL</c>-compatible layout.
    inline const float *MatrixElements() const;
    //! Tells the size in bytes of the encapsuled 4x4 matrix in <c>OpenGL</c>-compatible layout.
    inline uint32_t MatrixSize() const;
    
  protected:
    inline void InitAsIdentity();
  
    friend class FullTransform;
  
    float matrix_[4][4];    // Storage is column-major.
                            //
                            // Old comment: we represent the transformation as 4x4 matrix in a way compatible with
                            // OpenGL. Note that as a result, the matrix's memory layout is actually the transpose of
                            // the German convention for such transform matrices. When in the following we talk about
                            // matrix columns and rows, we refer to the conventions used in Germany.
};

const float *TransformCore::MatrixElements() const {
    return &matrix_[0][0];
}

uint32_t TransformCore::MatrixSize() const {
    return sizeof(matrix_);
}

void TransformCore::InitAsIdentity() {
    matrix_[0][0] = 1.0f;  matrix_[0][1] = 0.0f;  matrix_[0][2] = 0.0f;  matrix_[0][3] = 0.0f;
    matrix_[1][0] = 0.0f;  matrix_[1][1] = 1.0f;  matrix_[1][2] = 0.0f;  matrix_[1][3] = 0.0f;
    matrix_[2][0] = 0.0f;  matrix_[2][1] = 0.0f;  matrix_[2][2] = 1.0f;  matrix_[2][3] = 0.0f;
    matrix_[3][0] = 0.0f;  matrix_[3][1] = 0.0f;  matrix_[3][2] = 0.0f;  matrix_[3][3] = 1.0f;
}

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_TRANSFORMCORE_H_
