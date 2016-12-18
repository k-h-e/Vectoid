#ifndef KXM_VECTOID_COLLISIONCHECKER_H_
#define KXM_VECTOID_COLLISIONCHECKER_H_

#include <kxm/Core/ReusableItems.h>

#include <kxm/Core/logging.h>

namespace kxm {
namespace Vectoid {

class CollidableInterface;

//! Checks for collisions between groups of objects.
/*! 
 *  \ingroup Vectoid
 *
 *  The id type must be copyable.
 */
template<class IdType>
class CollisionChecker {
  public:
    CollisionChecker(int numCollisionGroups);
    CollisionChecker(const CollisionChecker &other)            = delete;
    CollisionChecker &operator=(const CollisionChecker &other) = delete;
    CollisionChecker(CollisionChecker &&other)                 = delete;
    CollisionChecker &operator=(CollisionChecker &&other)      = delete;
    
    //! Registers the specified collidable as member of the specified collidable group (as weak reference), and returns
    //! a non-negative id for unregistering it later.
    int Register(const IdType &id, CollidableInterface *collidable, int collisionGroup);
    //! Unregisters the specified collidable.
    void Unregister(int id);
    //! Configures the specified group pair to be included in the checks.
    void IncludeChecksForGroupPair(int group0, int group1);
    //! Performs the configured collision checks.
    void Check();
    
  private:
    struct CollidableInfo {
        IdType              id;
        CollidableInterface *collidable;
        CollidableInfo() : collidable(nullptr) {}
        CollidableInfo(const IdType &anId, CollidableInterface *aCollidable) : id(anId), collidable(aCollidable) {}
    };
    struct GroupPair {
        int group0,
            group1;
        GroupPair() : group0(0), group1(0) {}
        GroupPair(int aGroup0, int aGroup1) : group0(aGroup0), group1(aGroup1) {}
    };
    Core::ReusableItems<CollidableInfo> collidables_;
    std::vector<GroupPair>              groupPairsToCheck_;
};

template<class IdType>
CollisionChecker<IdType>::CollisionChecker(int numCollisionGroups)
        : collidables_(numCollisionGroups) {
    // Nop.
}

template<class IdType>
int CollisionChecker<IdType>::Register(const IdType &id, CollidableInterface *collidable, int collisionGroup) {
    int storageId;
    collidables_.Get(collisionGroup, &storageId) = CollidableInfo(id, collidable);
    return storageId;
}

template<class IdType>
void CollisionChecker<IdType>::Unregister(int id) {
    collidables_.Put(id);
}

template<class IdType>
void CollisionChecker<IdType>::IncludeChecksForGroupPair(int group0, int group1) {
    groupPairsToCheck_.push_back(GroupPair(group0, group1));
}

template<class IdType>
void CollisionChecker<IdType>::Check() {
    for (GroupPair &pair : groupPairsToCheck_) {
        auto iter0 = collidables_.GetIterator(pair.group0);
        while (CollidableInfo *info0 = iter0.Next()) {
            auto iter1 = collidables_.GetIterator(pair.group1);
            while (CollidableInfo *info1 = iter1.Next()) {
                // Perform check...
            }
        }
    }
}

}    // Namespace Vectoid.
}    // Namespace kxm.

#endif    // KXM_VECTOID_COLLISIONCHECKER_H_
