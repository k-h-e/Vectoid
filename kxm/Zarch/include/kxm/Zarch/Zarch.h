//
//  Zarch.h
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#ifndef KXM_ZARCH_ZARCH_H_
#define KXM_ZARCH_ZARCH_H_


#include <kxm/Game/EventQueue.h>
#include <kxm/Zarch/GameLogic/GameLogic.h>
#include <kxm/Zarch/Physics/Physics.h>
#include <kxm/Zarch/Video/Video.h>
#include <kxm/Zarch/events.h>

/*!
 *  \defgroup Zarch Zarch-like Game
 */


namespace kxm {

namespace Core {
    class ThreadingFactoryInterface;
    class Thread;
}
namespace Vectoid {
    class PerspectiveProjection;
}
namespace Game {
    class ThreadCouplingBuffer;
}

namespace Zarch {

class Simulation;
class Presentation;
class MapParameters;

//! Ties together the various <c>Zarch</c> game subsystems.
/*!
 *  \ingroup Zarch
 */
class Zarch {
  public:
    Zarch(boost::shared_ptr<Core::ThreadingFactoryInterface> threadingFactory);
    ~Zarch();
    void Execute(const Game::FrameTimeProcess::FrameTimeInfo &timeInfo,
                 const ControlsState &controlsState);
    void SetViewPort(int width, int height);
    void RenderFrame();
    //! Registers <c>Zarch</c> game events with the specified event queue, and creates and attaches
    //! the required event pools.
    static void RegisterEvents(Game::EventQueue<ZarchEvent::EventType> *eventQueue);
    
  private:
    Zarch(const Zarch &other);
    Zarch &operator=(const Zarch &other);
    
    Game::EventQueue<ZarchEvent::EventType>           eventQueue_;    // Will be deleted last.
    boost::shared_ptr<GameLogic>                      gameLogic_;
    boost::shared_ptr<Physics>                        physics_;
    boost::shared_ptr<Video>                          video_;
    boost::shared_ptr<Vectoid::PerspectiveProjection> projection_;
    boost::shared_ptr<MapParameters>                  mapParameters_;
    
    boost::shared_ptr<Simulation>                      simulation_;
    boost::shared_ptr<Presentation>                    presentation_;
    boost::shared_ptr<Game::ThreadCouplingBuffer>      simulationCouplingBuffer_;
    boost::shared_ptr<Core::ThreadingFactoryInterface> threadingFactory_;
    boost::shared_ptr<Core::Thread>                    simulationThread_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_ZARCH_H_

