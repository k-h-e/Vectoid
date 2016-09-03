#ifndef KXM_ZARCH_SIMULATION_H_
#define KXM_ZARCH_SIMULATION_H_


#include <memory>

#include <kxm/Core/ActionInterface.h>
#include <Zarch/Events/ZarchEvent.h>
#include <Zarch/EventHandlerCore.h>


namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
    class EventLoopHub;
}

namespace Zarch {

class InitializationEvent;
class PhysicsUpdatedEvent;
class FrameGeneratedEvent;

namespace GameLogic {
    class GameLogic;
}

namespace Physics {
    class Physics;
}

//! Ties together the simulation subsytems, that together run on the dedicated simulation thread (as
//! opposed to the main UI thread).
/*!
 *  \ingroup Zarch
 */
class Simulation : public EventHandlerCore, public virtual Core::ActionInterface {
  public:
    Simulation(const std::shared_ptr<Game::EventLoopHub> &eventLoopHub);
    ~Simulation();
    void ExecuteAction();
    void Handle(const InitializationEvent &event);
    void Handle(const PhysicsUpdatedEvent &event);
    void Handle(const FrameGeneratedEvent &event);

  private:
    Simulation(const Simulation &other);
    Simulation &operator=(const Simulation &other);
    void DoPhysicsTrigger();
    
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop_;
    std::shared_ptr<GameLogic::GameLogic>                          gameLogic_;
    std::shared_ptr<Physics::Physics>                              physics_;
    bool                                                           physicsUpdated_,
                                                                   frameGenerated_;
};

}
}


#endif    // KXM_ZARCH_SIMULATION_H_

