#ifndef KXM_ZARCH_PHYSICS_DATA_H_
#define KXM_ZARCH_PHYSICS_DATA_H_

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {

class MapParameters;
class Terrain;

namespace Physics {

struct Data {
    Data() : updateDeltaTimeS(0.0f) {}
    float                                                          updateDeltaTimeS;
    std::shared_ptr<MapParameters>                                 mapParameters;
    std::shared_ptr<Terrain>                                       terrain;
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop;
};

}    // Namespace Physics
}    // Namespace Zarch
}    // Namespace kxm

#endif    // KXM_ZARCH_PHYSICS_DATA_H_
