#ifndef KXM_ZARCH_GAMELOGIC_DATA_H_
#define KXM_ZARCH_GAMELOGIC_DATA_H_

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {
namespace GameLogic {

struct Data {
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop;
};

}    // Namespace Physics
}    // Namespace Zarch
}    // Namespace kxm

#endif    // KXM_ZARCH_GAMELOGIC_DATA_H_
