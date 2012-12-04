//
//  Physics.h
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#ifndef KXM_ZARCH_PHYSICS_PHYSICS_H_
#define KXM_ZARCH_PHYSICS_PHYSICS_H_


#include <kxm/Game/EventHandlerInterface.h>
#include <kxm/Game/Processes.h>
#include <kxm/Game/FrameTimeProcess.h>
#include <kxm/Zarch/events.h>
#include <kxm/Zarch/processes.h>

namespace kxm {

namespace Game {
    template<class T> class EventQueue;
}

namespace Vectoid {
    class CoordSysInterface;
    class Particles;
}

namespace Zarch {

class MapParameters;
class Terrain;
class ControlsState;

//! Physics subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup Zarch
 */
class Physics : public virtual Game::EventHandlerInterface {
  public:
    //! Event queue is passed as weak reference.
    Physics(
        Game::EventQueue<ZarchEvent::EventType> *eventQueue,
        boost::shared_ptr<MapParameters> mapParameters, boost::shared_ptr<Terrain> terrain,
        boost::shared_ptr<Vectoid::CoordSysInterface> landerCoordSys,
        boost::shared_ptr<Vectoid::Particles> thrusterParticles,
        boost::shared_ptr<Vectoid::Particles> shotsParticles);
    void HandleEvent(const Game::Event *event);
    void ExecuteProcesses();
    
  private:
    Physics(const Physics &other);
    Physics &operator=(const Physics &other);
    
    Game::Processes<ZarchProcess::ProcessType>               processes_;
    ZarchProcess::Context                                    processContext_;
    boost::shared_ptr<Game::FrameTimeProcess::FrameTimeInfo> frameTimeInfo_;
    boost::shared_ptr<ControlsState>                         controlsState_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_PHYSICS_PHYSICS_H_
