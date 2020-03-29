#ifndef KXM_VECTOID_COLLISIONCHECKERINTERFACE_H_
#define KXM_VECTOID_COLLISIONCHECKERINTERFACE_H_

#include <kxm/Core/Interface.h>

namespace kxm {
namespace Vectoid {

template<typename T> class Transform;
class BoundingBoxCollisionChecker;
class PointCollisionChecker;

//! Interface to objects performing collision checks between pairs of objects using a double-dispatch scheme.
/*! 
 *  \ingroup Vectoid
 */ 
class CollisionCheckerInterface : public virtual Core::Interface {
  public:
    //! Checks for collision with the specified other collision checker.
    /*!
     *  \return <c>true</c> in case a collision was detected.
     */
    virtual bool CheckCollision(CollisionCheckerInterface *other, const Transform<float> &otherTransform,
                                const Transform<float> &ourTransform) = 0;
    //! Checks for collision with the specified bounding box.
    /*!
     *  \return <c>true</c> in case a collision was detected.
     */
    virtual bool CheckCollision(BoundingBoxCollisionChecker *other, const Transform<float> &otherTransform,
                                const Transform<float> &ourTransform) = 0;
    //! Checks for collision with the specified point.
    /*!
     *  \return <c>true</c> in case a collision was detected.
     */
    virtual bool CheckCollision(PointCollisionChecker *other, const Transform<float> &otherTransform,
                                const Transform<float> &ourTransform) = 0;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_COLLISIONCHECKERINTERFACE_H_
