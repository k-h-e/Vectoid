#ifndef KXM_VECTOID_COLLIDER_H_
#define KXM_VECTOID_COLLIDER_H_

#include <kxm/Core/ReusableItems.h>
#include <kxm/Core/logging.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/CollidableInterface.h>
#include <kxm/Vectoid/CollisionCheckerInterface.h>

namespace kxm {
namespace Vectoid {

//! Checks for collisions between groups of collidables.
/*! 
 *  \ingroup Vectoid
 */
class Collider {
  public:
    Collider(int numCollisionGroups);
    Collider(const Collider &other)            = delete;
    Collider &operator=(const Collider &other) = delete;
    Collider(Collider &&other)                 = delete;
    Collider &operator=(Collider &&other)      = delete;
    
    //! Registers the specified collidable as member of the specified collidable group (as weak reference), and returns
    //! a non-negative id for unregistering it later.
    int Register(CollidableInterface *collidable, int collisionGroup);
    //! Unregisters the specified collidable.
    void Unregister(int id);
    //! Configures the specified group pair to be included in the checks.
    void IncludeChecksForGroupPair(int group0, int group1);
    //! Performs the configured collision checks.
    void Check();
    
  private:
    struct GroupPair {
        int group0,
            group1;
        GroupPair() : group0(0), group1(0) {}
        GroupPair(int aGroup0, int aGroup1) : group0(aGroup0), group1(aGroup1) {}
    };
    Core::ReusableItems<CollidableInterface *> collidables_;
    std::vector<GroupPair>                     groupPairsToCheck_;
};

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_COLLIDER_H_
