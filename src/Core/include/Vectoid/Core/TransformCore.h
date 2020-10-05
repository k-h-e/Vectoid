#ifndef VECTOID_CORE_TRANSFORMCORE_H_
#define VECTOID_CORE_TRANSFORMCORE_H_

#include <K/Core/NumberTools.h>
#include <Vectoid/Core/Vector.h>

namespace Vectoid {
namespace Core {

//! Base class to 3D transforms.
template<typename T>
class TransformCore {
  public:
    // No element initialization during construction, subclasses must do this! Want to avoid duplicate element
    // initializations for performance reasons.
    
    // Default copy, ok.
  
    //! Provides read access to the elements of the encapsuled 4x4 matrix in <c>OpenGL</c>-compatible layout.
    inline const T *MatrixElements() const;
    //! Tells the size in bytes of the encapsuled 4x4 matrix in <c>OpenGL</c>-compatible layout.
    inline uint32_t MatrixSize() const;
    
  protected:
    inline void InitAsIdentity();
  
    friend class FullTransform;
  
    T matrix_[4][4];    // Storage is column-major.
                        //
                        // Old comment: we represent the transformation as 4x4 matrix in a way compatible with OpenGL.
                        // Note that as a result, the matrix's memory layout is actually the transpose of the German
                        // convention for such transform matrices. When in the following we talk about matrix columns
                        // and rows, we refer to the conventions used in Germany.
};

template<typename T>
const T *TransformCore<T>::MatrixElements() const {
    return &matrix_[0][0];
}

template<typename T>
uint32_t TransformCore<T>::MatrixSize() const {
    return static_cast<uint32_t>(sizeof(matrix_));
}

template<typename T>
void TransformCore<T>::InitAsIdentity() {
    matrix_[0][0] = 1.0f;
    matrix_[0][1] = 0.0f;
    matrix_[0][2] = 0.0f;
    matrix_[0][3] = 0.0f;

    matrix_[1][0] = 0.0f;
    matrix_[1][1] = 1.0f;
    matrix_[1][2] = 0.0f;
    matrix_[1][3] = 0.0f;

    matrix_[2][0] = 0.0f;
    matrix_[2][1] = 0.0f;
    matrix_[2][2] = 1.0f;
    matrix_[2][3] = 0.0f;

    matrix_[3][0] = 0.0f;
    matrix_[3][1] = 0.0f;
    matrix_[3][2] = 0.0f;
    matrix_[3][3] = 1.0f;
}

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_TRANSFORMCORE_H_
