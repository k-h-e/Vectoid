#ifndef KXM_ZARCH_AI_DATA_H_
#define KXM_ZARCH_AI_DATA_H_

#include <memory>
#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class MapParameters;
class Terrain;

namespace AI {

//! AI data.
/*!
 *  \ingroup ZarchAI
 */
struct Data {
    Data() : updateDeltaTime_s(0.0f) {}
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop;
    float                                                          updateDeltaTime_s;
    std::shared_ptr<MapParameters>                                 mapParameters;
    std::shared_ptr<Terrain>                                       terrain;
};

}    // Namespace AI.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_AI_DATA_H_
