#ifndef KXM_VECTOID_BOUNDINGBOXCOLLISIONCHECKER_H_
#define KXM_VECTOID_BOUNDINGBOXCOLLISIONCHECKER_H_

#include <kxm/Vectoid/CollisionCheckerInterface.h>

namespace kxm {
namespace Vectoid {

template<typename T> class BoundingBox;
template<typename T> class Transform;

//! Adapts a bounding box for taking part in collision checking.
/*! 
 *  \ingroup Vectoid
 */ 
class BoundingBoxCollisionChecker : public virtual CollisionCheckerInterface {
  public:
    //! The specified bounding box object is expected to outlive the constructed checker instance.
    BoundingBoxCollisionChecker(const BoundingBox<float> &boundingBox);
    bool CheckCollision(CollisionCheckerInterface *other, const Transform<float> &otherTransform,
                        const Transform<float> &ourTransform);
    bool CheckCollision(BoundingBoxCollisionChecker *other, const Transform<float> &otherTransform,
                        const Transform<float> &ourTransform);
    bool CheckCollision(PointCollisionChecker *other, const Transform<float> &otherTransform,
                        const Transform<float> &ourTransform);
    
  private:
    const BoundingBox<float> &boundingBox_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_BOUNDINGBOXCOLLISIONCHECKER_H_
