//
//  NewPhysics.h
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#ifndef KXM_ZARCH_PHYSICS_H_
#define KXM_ZARCH_PHYSICS_H_


#include <memory>

#include <Vectoid/Transform.h>
#include <Game/EventHandlerInterface.h>
#include <Zarch/ControlsState.h>
#include <Zarch/processes.h>


namespace kxm {

namespace Game {
    class EventQueue;
    template<class T> class Processes;
}

namespace Zarch {

class VariantEvent;
class MapParameters;
class Terrain;
class FrameTimeEvent;
class ControlsStateEvent;

//! Physics subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup Zarch
 */
class Physics : public virtual Game::EventHandlerInterface {
  public:
    struct LanderState {
        LanderState() : thrusterEnabled(false), firingEnabled(false) {}
        Vectoid::Transform transform;
        Vectoid::Vector    velocity;
        bool               thrusterEnabled, firingEnabled;
    };
    struct Data {
        Data() : frameDeltaTimeS(0.0f) {}
        float                             frameDeltaTimeS;
        ControlsState                     controlsState;
        LanderState                       landerState;
        std::shared_ptr<MapParameters>    mapParameters;
        std::shared_ptr<Terrain>          terrain;
        std::shared_ptr<Game::EventQueue> eventQueue;
    };
    
    Physics(std::shared_ptr<Game::EventQueue> eventQueue,
            std::shared_ptr<Game::Processes<ZarchProcess::ProcessType>> processes);
    ~Physics();
    void HandleEvent(const Game::Event &event);
    void HandleFrameTimeEvent(const FrameTimeEvent &event);
    void HandleControlsStateEvent(const ControlsStateEvent &event);
    
  private:
    Physics(const Physics &other);
    Physics &operator=(const Physics &other);

    std::shared_ptr<Game::EventQueue>                           eventQueue_;
    std::shared_ptr<Game::Processes<ZarchProcess::ProcessType>> processes_;
    std::shared_ptr<Data>                                       data_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_PHYSICS_H_
