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
 */
template<class ActorType>
class ReusableActors {
  public:
    class Iterator;
  
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
    ActorType *Get(int *outStorageId);
    //! Puts back the specified actor for re-use.
    /*!
     *  The actor gets unregistered as action from the <c>Actions</c> object that was passed to the actor collection
     *  upon construction.
     */
    void Put(int storageId);
    //! Returns an iterator for the currently in-use actors.
    Iterator GetIterator();
    
  private:
    struct ActorInfo {
        std::shared_ptr<ActorType> actor;
        int                        actionStorageId;
        ActorInfo() : actionStorageId(0) {}
    };
  
    Core::ReusableItems<ActorInfo> actors_;
    std::shared_ptr<Actions>       actions_;
};

//! Allows for iterating over the actors that are currently in use.
/*!
 *  \ingroup Game
 */
template<class ActorType>
class ReusableActors<ActorType>::Iterator {
  public:
    //! Returns the next item, or <code>0</code> in case there are no more items.
    ActorType *Next();
    //! If the iterator has returned an item in the last call to \ref Next(), this item's id is
    //! returned. Otherwise, the method's behavior is undefined.
    /*!
     *  The current item can be \ref Put() back using the returned id without invalidating the iterator.
     */
    int ItemId();
    
  private:
    friend class ReusableActors;
    Iterator(const typename Core::ReusableItems<ActorInfo>::Iterator &iterator);
    
    typename Core::ReusableItems<ActorInfo>::Iterator iterator_;
};


template<class ActorType>
ActorType *ReusableActors<ActorType>::Get(int *outStorageId) {
    ActorInfo &info = actors_.Get(0, outStorageId);
    if (!info.actor) {
        info.actor = std::shared_ptr<ActorType>(new ActorType());
    }
    info.actionStorageId = actions_->Register(info.actor.get());
    return info.actor.get();
}

template<class ActorType>
void ReusableActors<ActorType>::Put(int storageId) {
    ActorInfo &info = actors_.Item(storageId);
    actions_->Unregister(info.actionStorageId);
    actors_.Put(storageId);
}

template<class ActorType>
typename ReusableActors<ActorType>::Iterator ReusableActors<ActorType>::GetIterator() {
    return Iterator(actors_.GetIterator(0));
}

template<class ActorType>
ReusableActors<ActorType>::Iterator::Iterator(const typename Core::ReusableItems<ActorInfo>::Iterator &iterator)
        : iterator_(iterator) {
    // Nop.
}

template<class ActorType>
ActorType *ReusableActors<ActorType>::Iterator::Next() {
    ActorInfo *info = iterator_.Next();
    if (info) {
        return info->actor.get();
    }
    else {
        return nullptr;
    }
}

template<class ActorType>
int ReusableActors<ActorType>::Iterator::ItemId() {
    return iterator_.ItemId();
}

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_REUSABLEACTORS_H_
