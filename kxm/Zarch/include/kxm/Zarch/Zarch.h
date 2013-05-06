//
//  Zarch.h
//  kxm
//
//  Created by Kai Hergenröther on 12/3/12.
//
//


#ifndef KXM_ZARCH_ZARCH_H_
#define KXM_ZARCH_ZARCH_H_


/*!
 *  \defgroup Zarch Zarch-like Game
 */


#include <boost/shared_ptr.hpp>

#include <kxm/Zarch/Presentation.h>
#include <kxm/Zarch/events.h>


namespace kxm {

namespace Core {
    class ThreadingFactoryInterface;
    class Thread;
}
namespace Game {
    class ThreadCouplingBuffer;
    template<class T> class EventQueue;
}

namespace Zarch {

class Simulation;
class ControlsState;

//! Ties together the various <c>Zarch</c> game subsystems.
/*!
 *  \ingroup Zarch
 */
class Zarch {
  public:
    Zarch(boost::shared_ptr<Core::ThreadingFactoryInterface> threadingFactory);
    ~Zarch();
    void PrepareFrame(const ControlsState &controlsState) {
        presentation_->PrepareFrame(controlsState);
    }
    void SetViewPort(int width, int height) {
        presentation_->SetViewPort(width, height);
    }
    void RenderFrame() {
        presentation_->RenderFrame();
    }
    //! Registers <c>Zarch</c> game events with the specified event queue, and creates and attaches
    //! the required event pools.
    static void RegisterEvents(Game::EventQueue<ZarchEvent::EventType> *eventQueue);
    
  private:
    Zarch(const Zarch &other);
    Zarch &operator=(const Zarch &other);
    
    boost::shared_ptr<Simulation>                      simulation_;
    boost::shared_ptr<Presentation>                    presentation_;
    boost::shared_ptr<Game::ThreadCouplingBuffer>      simulationCouplingBuffer_;
    boost::shared_ptr<Core::ThreadingFactoryInterface> threadingFactory_;
    boost::shared_ptr<Core::Thread>                    simulationThread_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_ZARCH_H_

