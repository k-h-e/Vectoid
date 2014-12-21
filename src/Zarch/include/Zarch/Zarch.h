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


#include <memory>

#include <Zarch/Presentation.h>


namespace kxm {

namespace Core {
    class ThreadingFactoryInterface;
    class Thread;
}
namespace Game {
    class EventQueueHub;
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
    Zarch(std::shared_ptr<Core::ThreadingFactoryInterface> threadingFactory);
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
    
    //! Registers all <c>Zarch</c> game events with the specified event queue.
    static void RegisterEvents(Game::EventQueue *eventQueue);
    
  private:
    Zarch(const Zarch &other);
    Zarch &operator=(const Zarch &other);
    
    std::shared_ptr<Simulation>                      simulation_;
    std::shared_ptr<Presentation>                    presentation_;
    std::shared_ptr<Game::EventQueueHub>             eventQueueHub_;
    std::shared_ptr<Core::ThreadingFactoryInterface> threadingFactory_;
    std::shared_ptr<Core::Thread>                    simulationThread_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_ZARCH_H_

