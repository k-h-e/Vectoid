#ifndef KXM_VECTOID_FULLTRANSFORM_H_
#define KXM_VECTOID_FULLTRANSFORM_H_

#include <kxm/Vectoid/TransformCore.h>

namespace kxm {
namespace Vectoid {

//! Full 3D transform (not limited to rotations, translations and combinations thereof).
/*!
 *  \ingroup Vectoid
 */
class FullTransform : public TransformCore {
  public:
    //! Initializes the transform to the identity.
    inline FullTransform();
};

FullTransform::FullTransform() {
    matrix_[0][0] = 1.0f;  matrix_[0][1] = 0.0f;  matrix_[0][2] = 0.0f;  matrix_[0][3] = 0.0f;
    matrix_[1][0] = 0.0f;  matrix_[1][1] = 1.0f;  matrix_[1][2] = 0.0f;  matrix_[1][3] = 0.0f;
    matrix_[2][0] = 0.0f;  matrix_[2][1] = 0.0f;  matrix_[2][2] = 1.0f;  matrix_[2][3] = 0.0f;
    matrix_[3][0] = 0.0f;  matrix_[3][1] = 0.0f;  matrix_[3][2] = 0.0f;  matrix_[3][3] = 1.0f;
}

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_FULLTRANSFORM_H_

