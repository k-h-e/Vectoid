///////////////////////////////////////////////////////////////////////////////      //                               //
//                                                                                  //                 //            //
//    vectoid 3D Graphics & Processing         //       //  ///////     ///////  //////    ///////            ////////
//    (C) Copyright Kai Hergenröther          //     //   //      //  //      //  //     //      //  //     //     //
//                                           //   //    //////////  //           //    //        // //    //      //
//                                          // //       //          //      //  //     //      //  //     //     //
///////////////////////////////////////    ///          /////////   ////////    /////  ////////    /////  ////////

#ifndef VECTOID_CORE_COLLIDER_H_
#define VECTOID_CORE_COLLIDER_H_

#include <K/Core/ReusableItems.h>
#include <K/Core/Log.h>
#include <Vectoid/Core/Transform.h>
#include <Vectoid/Core/CollidableInterface.h>
#include <Vectoid/Core/CollisionCheckerInterface.h>

namespace Vectoid {
namespace Core {

template<typename T> class Transform;

//! Checks for collisions between groups of collidables.
/*! 
 *  The id type must be default-constructible and copyable.
 */
template<class IdType>
class Collider {
  public:
    class DelegateInterface : public K::Core::Interface {
      public:
        virtual void ModifyOtherTransform(Transform<float> *inOutOtherTransform,
                                          const Transform<float> &ourTransform) = 0;
        virtual void HandleCollision(const IdType &id, const IdType &otherId) = 0;
    };
  
    //! The delegate, if specified, must be guaranteed to live as long as the collider - the collider's destructor won't
    //! call into the delegate, though.
    Collider(int numCollisionGroups, DelegateInterface *delegate = 0);
    Collider(const Collider &other)            = delete;
    Collider &operator=(const Collider &other) = delete;
    Collider(Collider &&other)                 = delete;
    Collider &operator=(Collider &&other)      = delete;
    
    //! Registers the specified collidable as member of the specified collidable group (as weak reference), and returns
    //! a non-negative storage id for unregistering it later.
    int Register(const IdType &id, CollidableInterface *collidable, int collisionGroup);
    //! Unregisters the specified collidable.
    void Unregister(int storageId);
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
    
    struct CollidableInfo {
        IdType              id;
        CollidableInterface *collidable;
        CollidableInfo(const IdType &anId, CollidableInterface *aCollidable)
            : id(anId),
              collidable(aCollidable) {}
        CollidableInfo()
            : id(),
              collidable(nullptr) {}
  
    };
    
    K::Core::ReusableItems<CollidableInfo> collidables_;
    std::vector<GroupPair>                 groupPairsToCheck_;
    DelegateInterface                      *delegate_;
};

template<class IdType>
Collider<IdType>::Collider(int numCollisionGroups, DelegateInterface *delegate)
        : collidables_(numCollisionGroups),
          delegate_(delegate) {
    // Nop.
}

template<class IdType>
int Collider<IdType>::Register(const IdType &id, CollidableInterface *collidable, int collisionGroup) {
    int storageId;
    CollidableInfo &info = collidables_.Get(collisionGroup, &storageId);
    info.id         = id;
    info.collidable = collidable;
    return storageId;
}

template<class IdType>
void Collider<IdType>::Unregister(int storageId) {
    collidables_.Put(storageId);
}

template<class IdType>
void Collider<IdType>::IncludeChecksForGroupPair(int group0, int group1) {
    groupPairsToCheck_.push_back(GroupPair(group0, group1));
}

template<class IdType>
void Collider<IdType>::Check() {
    Transform<float> transform0, transform1;
    for (GroupPair &pair : groupPairsToCheck_) {
        for (CollidableInfo &info0 : collidables_.Iterate(pair.group0)) {
            info0.collidable->GetTransform(&transform0);
            for (CollidableInfo &info1 : collidables_.Iterate(pair.group1)) {
                info1.collidable->GetTransform(&transform1);
                if (delegate_) {
                    delegate_->ModifyOtherTransform(&transform1, transform0);
                }
                if (info0.collidable->CollisionChecker()->CheckCollision(info1.collidable->CollisionChecker(),
                                                                         transform1, transform0)) {
                    if (delegate_) {
                        delegate_->HandleCollision(info0.id, info1.id);
                    }
                }
            }
        }
    }
}

}    // Namespace Core.
}    // Namespace Vectoid.

#endif    // VECTOID_CORE_COLLIDER_H_
