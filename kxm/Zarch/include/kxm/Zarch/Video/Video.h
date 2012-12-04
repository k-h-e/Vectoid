//
//  Video.h
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#ifndef KXM_ZARCH_VIDEO_VIDEO_H_
#define KXM_ZARCH_VIDEO_VIDEO_H_


#include <kxm/Game/EventHandlerInterface.h>
#include <kxm/Game/Processes.h>
#include <kxm/Zarch/Physics/LanderProcess.h>
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
class TerrainRenderer;

//! Video subsystem for the <c>Zarch</c> game.
/*!
 *  \ingroup Zarch
 */
class Video : public virtual Game::EventHandlerInterface {
  public:
    //! Event queue is passed as weak reference.
    Video(Game::EventQueue<ZarchEvent::EventType> *eventQueue,
          boost::shared_ptr<MapParameters> mapParameters,
          boost::shared_ptr<Vectoid::CoordSysInterface> camera,
          boost::shared_ptr<TerrainRenderer> terrainRenderer,
          boost::shared_ptr<Vectoid::Particles> starFieldParticles);
    void HandleEvent(const Game::Event *event);
    void ExecuteProcesses();
    
  private:
    Video(const Video &other);
    Video &operator=(const Video &other);
    
    Game::Processes<ZarchProcess::ProcessType>        processes_;
    ZarchProcess::Context                             processContext_;
    boost::shared_ptr<LanderProcess::LanderStateInfo> landerStateInfo_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_VIDEO_VIDEO_H_
