#ifndef KXM_GAME_REUSABLEACTORS_H_
#define KXM_GAME_REUSABLEACTORS_H_

#include <memory>
#include <kxm/Core/ReusableItems.h>
#include <Game/Actions.h>

namespace kxm {
namespace Game {

//! Actor collection, allowing reuse of actors.
/*!
 *  \ingroup Game
 *
 *  The in-use actors are automatically registered as actions with the <c>Actions</c> object that was passed to the
 *  actor collection upon construction. Likewise, they get automatically unregistered when they are put back.
 *
 *  The actor type must have a public field <c>int reusableActorStorageId</c>.
 */
template<class ActorType>
class ReusableActors {
  public:
    ReusableActors(std::shared_ptr<Actions> actions) : actors_(1), actions_(actions) {};
    ReusableActors(const ReusableActors &other)            = delete;
    ReusableActors &operator=(const ReusableActors &other) = delete;
    ReusableActors(ReusableActors &&other)                 = delete;
    ReusableActors &operator=(ReusableActors &&other)      = delete;
    //! Provides another actor for use via dumb pointer, yet ownership remains with the collection.
    /*!
     *  The new actor gets registered as action with the <c>Actions</c> object that was passed to the actor collection
     *  upon construction.
     */
    ActorType *Get();
    //! Puts back the specified actor for re-use.
    /*!
     *  The actor gets unregistered as action from the <c>Actions</c> object that was passed to the actor collection
     *  upon construction.
     */
    void Put(ActorType *actor);
    
  private:
    struct ActorInfo {
        std::shared_ptr<ActorType> actor;
        int                        actionStorageId;
        ActorInfo() : actionStorageId(0) {}
    };
  
    Core::ReusableItems<ActorInfo> actors_;
    std::shared_ptr<Actions>       actions_;
};

template<class ActorType>
ActorType *ReusableActors<ActorType>::Get() {
    int storageId;
    ActorInfo &info = actors_.Get(0, &storageId);
    if (!info.actor) {
        info.actor = std::shared_ptr<ActorType>(new ActorType());
    }
    info.actor->reusableActorsStorageId = storageId;
    info.actionStorageId = actions_->Register(info.actor.get());
    return info.actor.get();
}

template<class ActorType>
void ReusableActors<ActorType>::Put(ActorType *actor) {
    ActorInfo &info = actors_.Item(actor->reusableActorsStorageId);
    actions_->Unregister(info.actionStorageId);
    actors_.Put(actor->reusableActorsStorageId);
}

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_REUSABLEACTORS_H_
