/*!
 * \ingroup Zarch
 *
 * \defgroup ZarchPhysics Physics
 */

#ifndef KXM_ZARCH_PHYSICS_H_
#define KXM_ZARCH_PHYSICS_H_

#include <memory>

#include <Vectoid/Transform.h>
#include <Game/ProcessOwnerInterface.h>
#include <Game/ActorName.h>
#include <Zarch/ControlsState.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/EventHandlerCore.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class MapParameters;
class Terrain;
class ActorCreatedEvent;
class FrameTimeEvent;
class ControlsStateEvent;

namespace Physics {

class LanderProcess;

//! Physics subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup ZarchPhysics
 */
class Physics : public EventHandlerCore,
                public virtual Game::ProcessOwnerInterface {
  public:
    struct LanderState {
        LanderState() : thrusterEnabled(false), firingEnabled(false) {}
        Vectoid::Transform transform;
        Vectoid::Vector    velocity;
        bool               thrusterEnabled, firingEnabled;
    };
    struct Data {
        Data() : frameDeltaTimeS(0.0f) {}
        float                                                          frameDeltaTimeS;
        ControlsState                                                  controlsState;
        Game::ActorName                                                landerActor;
        LanderState                                                    landerState;
        std::shared_ptr<MapParameters>                                 mapParameters;
        std::shared_ptr<Terrain>                                       terrain;
        std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop;
    };
    
    Physics(std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop);
    ~Physics();
    void HandleProcessFinished(Game::ProcessInterface *process);
    void Handle(const UpdatePhysicsEvent &event);
    void Handle(const ActorCreatedEvent &event);
    void Handle(const FrameTimeEvent &event);
    void Handle(const ControlsStateEvent &event);
    
  private:
    Physics(const Physics &other);
    Physics &operator=(const Physics &other);

    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop_;
    std::shared_ptr<Data>                                          data_;
    std::unique_ptr<LanderProcess>                                 landerProcess_;
};

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PHYSICS_H_
