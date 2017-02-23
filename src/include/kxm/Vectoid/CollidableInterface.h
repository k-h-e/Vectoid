#ifndef KXM_VECTOID_COLLIDABLEINTERFACE_H_
#define KXM_VECTOID_COLLIDABLEINTERFACE_H_

#include <kxm/Core/Interface.h>

namespace kxm {
namespace Vectoid {

class Transform;
class CollidableBoundingBox;
class CollidablePoint;

//! Interface to objects taking part in collision checking.
/*! 
 *  \ingroup Vectoid
 */ 
class CollidableInterface : public virtual Core::Interface {
  public:
    //! Checks for collision with the specified other collidable.
    /*!
     *  \return <c>true</c> in case a collision was detected.
     */
    virtual bool CheckCollision(const CollidableInterface &other, const Transform &otherTransform,
                                const Transform &ourTransform) const = 0;
    //! Checks for collision with the specified bounding box.
    /*!
     *  \return <c>true</c> in case a collision was detected.
     */
    virtual bool CheckCollision(const CollidableBoundingBox &other, const Transform &otherTransform,
                                const Transform &ourTransform) const = 0;
    //! Checks for collision with the specified point.
    /*!
     *  \return <c>true</c> in case a collision was detected.
     */
    virtual bool CheckCollision(const CollidablePoint &other, const Transform &otherTransform,
                                const Transform &ourTransform) const = 0;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_COLLIDABLEINTERFACE_H_
