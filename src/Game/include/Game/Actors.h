#ifndef KXM_GAME_ACTORS_
#define KXM_GAME_ACTORS_

#include <assert.h>
#include <vector>
#include <Game/ActorId.h>

namespace kxm {
namespace Game {

//! Maps actor ids to actor objects.
/*!
 *  \ingroup Game
 */
template<class ActorType>
class Actors {
  public:
    Actors() {};
    Actors(const Actors &other)            = delete;
    Actors &operator=(const Actors &other) = delete;
    Actors(Actors &&other)                 = delete;
    Actors &operator=(Actors &&other)      = delete;
    //! Registers the specified actor under the given actor id.
    /*!
     *  Only a weak reference is kept to the actor - no ownership is assumed!
     *
     *  No actor must already be registered for the actor id's actual id component.
     */
    void Register(const ActorId &id, ActorType *actor);
    //! Unregisters the actor registered for the specified actor id, if such an actor is present.
    /*!
     *  The actor id's incarnation number must match for an unregistration to occur!
     *
     *  \return The actor if one was unregistered, or <c>nullptr</c> otherwise.
     */
    ActorType *Unregister(const ActorId &id);
    //! Returns the actor registered for the specified actor id, or <c>nullptr</c> if such an actor is not present.
    ActorType *Get(const ActorId &id);
    
  private:
    struct ActorInfo {
        uint32_t  incarnation;
        ActorType *actor;
        ActorInfo() : incarnation(0u), actor(nullptr) {}
    };
    std::vector<ActorInfo> actors_;
};

template<class ActorType>
void Actors<ActorType>::Register(const ActorId &id, ActorType *actor) {
    assert(id.id >= 0);
    assert(actor);
    while ((int)actors_.size() <= id.id) {
        actors_.push_back(ActorInfo());
    }
    ActorInfo &info = actors_[id.id];
    assert(!info.actor);
    info.incarnation = id.incarnation;
    info.actor       = actor;
}

template<class ActorType>
ActorType *Actors<ActorType>::Unregister(const ActorId &id) {
    ActorType *actor = Get(id);
    if (actor) {
        actors_[id.id].actor = nullptr;
    }
    return actor;
}

template<class ActorType>
ActorType *Actors<ActorType>::Get(const ActorId &id) {
    if ((id.id >= 0) && (id.id < (int)actors_.size())) {
        ActorInfo &info = actors_[id.id];
        if (info.actor && (info.incarnation == id.incarnation)) {
            return info.actor;
        }
    }
    return nullptr;
}

}    // NamespaceGame.
}    // Namespace kxm.

#endif    // KXM_GAME_ACTORS_
