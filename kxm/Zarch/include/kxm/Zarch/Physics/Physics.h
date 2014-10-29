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

#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/EventHandlerInterface.h>
#include <kxm/Zarch/ControlsState.h>
#include <kxm/Zarch/processes.h>


namespace kxm {

namespace Game {
    template<class T> class Processes;
}

namespace Zarch {

class VariantEvent;
class ControlsStateEvent;
class MapParameters;
class Terrain;

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
        float                          frameDeltaTimeS;
        ControlsState                  controlsState;
        LanderState                    landerState;
        std::shared_ptr<MapParameters> mapParameters;
        std::shared_ptr<Terrain>       terrain;
    };
    
    Physics(std::shared_ptr<Game::Processes<ZarchProcess::ProcessType>> processes);
    //! (Re)implemented.
    void HandleEvent(const Game::OldEvent &event);
    
  private:
    Physics(const Physics &other);
    Physics &operator=(const Physics &other);

    std::shared_ptr<Game::Processes<ZarchProcess::ProcessType>> processes_;
    std::shared_ptr<Data>                                       data_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_PHYSICS_H_
