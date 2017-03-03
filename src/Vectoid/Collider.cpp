#include <kxm/Vectoid/Collider.h>

#include <cstdio>

namespace kxm {
namespace Vectoid {

Collider::Collider(int numCollisionGroups)
        : collidables_(numCollisionGroups) {
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
        auto iter0 = collidables_.GetIterator(pair.group0);
        while (CollidableInterface **collidable0 = iter0.Next()) {
            (*collidable0)->GetTransform(&transform0);
            auto iter1 = collidables_.GetIterator(pair.group1);
            while (CollidableInterface **collidable1 = iter1.Next()) {
                (*collidable1)->GetTransform(&transform1);
                // TODO: Correct for word wrap-around.
                if ((*collidable0)->CollisionChecker()->CheckCollision((*collidable1)->CollisionChecker(), transform1,
                                                                       transform0)) {
                    std::puts("    COLLISION");
                }
            }
        }
    }
    std::puts("---");
}

}    // Namespace Vectoid.
}    // Namespace kxm.
