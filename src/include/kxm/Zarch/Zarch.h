#ifndef KXM_ZARCH_ZARCH_H_
#define KXM_ZARCH_ZARCH_H_

/*!
 *  \defgroup Zarch Zarch
 *  \brief Zarch-like game.
 */

#include <memory>
#include <thread>
#include <kxm/Zarch/Presentation.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
    class EventLoopHub;
}

namespace Zarch {

class Simulation;
class ControlsState;

namespace Video {
    class RenderTargetInterface;
}

//! Ties together the various <c>Zarch</c> game subsystems.
/*!
 *  \ingroup Zarch
 */
class Zarch {
  public:
    Zarch(const std::shared_ptr<Video::RenderTargetInterface> &renderTarget);
    Zarch(const Zarch &other) = delete;
    Zarch &operator=(const Zarch &other) = delete;
    ~Zarch();
    void PrepareFrame(const ControlsState &controlsState);
    void SetViewPort(int width, int height);
    void RenderFrame();
    
    //! Registers all <c>Zarch</c> game events with the specified event queue.
    static void RegisterEvents(Game::EventLoop<ZarchEvent, EventHandlerCore> *eventLoop);
    
  private:
    std::shared_ptr<Simulation>         simulation_;
    std::shared_ptr<Presentation>       presentation_;
    std::shared_ptr<Game::EventLoopHub> eventLoopHub_;
    std::shared_ptr<std::thread>        simulationThread_;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_ZARCH_H_
