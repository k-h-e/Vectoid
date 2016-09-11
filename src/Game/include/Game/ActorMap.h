#ifndef KXM_GAME_ACTORMAP_
#define KXM_GAME_ACTORMAP_

#include <cassert>
#include <vector>
#include <Game/ActorName.h>

namespace kxm {
namespace Game {

//! Maps actor names to actor objects.
/*!
 *  \ingroup Game
 */
template<class ActorType>
class ActorMap {
  public:
    ActorMap() {};
    ActorMap(const ActorMap &other)            = delete;
    ActorMap &operator=(const ActorMap &other) = delete;
    ActorMap(ActorMap &&other)                 = delete;
    ActorMap &operator=(ActorMap &&other)      = delete;
    //! Registers the specified actor under the given actor name.
    /*!
     *  Only a weak reference is kept to the actor - no ownership is assumed!
     *
     *  No actor must already be registered for the actor name's id component.
     */
    void Register(const ActorName &name, ActorType *actor);
    //! Unregisters the actor registered for the specified actor name, if such an actor is present.
    /*!
     *  The actor name's incarnation number must match for an unregistration to occur!
     *
     *  \return The actor if one was unregistered, or <c>nullptr</c> otherwise.
     */
    ActorType *Unregister(const ActorName &name);
    //! Returns the actor registered for the specified actor name, or <c>nullptr</c> if such an actor is not present.
    ActorType *Get(const ActorName &name);
    
  private:
    struct ActorInfo {
        uint32_t  incarnation;
        ActorType *actor;
        ActorInfo() : incarnation(0u), actor(nullptr) {}
    };
    std::vector<ActorInfo> actors_;
};

template<class ActorType>
void ActorMap<ActorType>::Register(const ActorName &name, ActorType *actor) {
    assert(!name.IsNone());
    assert(actor);
    while ((int)actors_.size() <= name.Id()) {
        actors_.push_back(ActorInfo());
    }
    ActorInfo &info = actors_[name.Id()];
    assert(!info.actor);
    info.incarnation = name.Incarnation();
    info.actor       = actor;
}

template<class ActorType>
ActorType *ActorMap<ActorType>::Unregister(const ActorName &name) {
    ActorType *actor = Get(name);
    if (actor) {
        actors_[name.Id()].actor = nullptr;
    }
    return actor;
}

template<class ActorType>
ActorType *ActorMap<ActorType>::Get(const ActorName &name) {
    if (!name.IsNone() && (name.Id() < (int)actors_.size())) {
        ActorInfo &info = actors_[name.Id()];
        if (info.actor && (info.incarnation == name.Incarnation())) {
            return info.actor;
        }
    }
    return nullptr;
}

}    // NamespaceGame.
}    // Namespace kxm.

#endif    // KXM_GAME_ACTORMAP_
