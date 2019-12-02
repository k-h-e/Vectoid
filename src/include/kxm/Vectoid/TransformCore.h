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
    //! Provides read access to the elements of the encapsuled 4x4 matrix in <c>OpenGL</c>-compatible layout.
    inline const float *MatrixElements() const;
    
  protected:
    float matrix_[4][4];    // We represent the transformation as 4x4 matrix in a way compatible with OpenGL. Note that
                            // as a result, the matrix's memory layout is actually the transpose of the German
                            // convention for such transform matrices. When in the following we talk about matrix
                            // columns and rows, we refer to the conventions used in Germany.
};

const float *TransformCore::MatrixElements() const {
    return &matrix_[0][0];
}

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_TRANSFORMCORE_H_
