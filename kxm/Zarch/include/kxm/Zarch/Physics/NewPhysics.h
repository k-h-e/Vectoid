//
//  NewPhysics.h
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#ifndef KXM_ZARCH_PHYSICS_NEWPHYSICS_H_
#define KXM_ZARCH_PHYSICS_NEWPHYSICS_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/EventHandlerInterface.h>
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
class NewPhysics : public virtual Game::EventHandlerInterface {
  public:
    struct LanderState {
        LanderState() : thrusterEnabled(false), firingEnabled(false) {}
        Vectoid::Transform transform;
        Vectoid::Vector    velocity;
        bool               thrusterEnabled, firingEnabled;
    };

    struct Data {
        Data() : frameDeltaTimeS(0.0f) {}
        float                            frameDeltaTimeS;
        ControlsState                    controlsState;
        LanderState                      landerState;
        boost::shared_ptr<MapParameters> mapParameters;
        boost::shared_ptr<Terrain>       terrain;
    };
    NewPhysics(boost::shared_ptr<Game::Processes<ZarchProcess::ProcessType> > processes);
    //! (Re)implemented.
    void HandleEvent(const Game::Event &event);
    
  private:
    NewPhysics(const NewPhysics &other);
    NewPhysics &operator=(const NewPhysics &other);
    void HandleTimeEvent(const VariantEvent &event);
    void HandleControlsStateEvent(const ControlsStateEvent &event);

    boost::shared_ptr<Game::Processes<ZarchProcess::ProcessType> > processes_;
    boost::shared_ptr<Data>                                        data_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_PHYSICS_NEWPHYSICS_H_
