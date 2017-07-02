#include <kxm/Vectoid/Collider.h>

#include <cstdio>

namespace kxm {
namespace Vectoid {

Collider::Collider(int numCollisionGroups, DelegateInterface *delegate)
        : collidables_(numCollisionGroups),
          delegate_(delegate) {
    // Nop.
}

int Collider::Register(CollidableInterface *collidable, int collisionGroup) {
    int storageId;
    collidables_.Get(collisionGroup, &storageId) = collidable;
    return storageId;
}

void Collider::Unregister(int id) {
    collidables_.Put(id);
}

void Collider::IncludeChecksForGroupPair(int group0, int group1) {
    groupPairsToCheck_.push_back(GroupPair(group0, group1));
}

void Collider::Check() {
    Transform transform0, transform1;
    for (GroupPair &pair : groupPairsToCheck_) {
        for (CollidableInterface *collidable0 : collidables_.Iterate(pair.group0)) {
            collidable0->GetTransform(&transform0);
            for (CollidableInterface *collidable1 : collidables_.Iterate(pair.group1)) {
                collidable1->GetTransform(&transform1);
                if (delegate_) {
                    delegate_->ModifyOtherTransform(&transform1, transform0);
                }
                if (collidable0->CollisionChecker()->CheckCollision(collidable1->CollisionChecker(), transform1,
                                                                    transform0)) {
                    std::puts("    COLLISION");
                    std::exit(0);
                }
            }
        }
    }
    std::puts("---");
}

}    // Namespace Vectoid.
}    // Namespace kxm.
