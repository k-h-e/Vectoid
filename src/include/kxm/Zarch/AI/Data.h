#ifndef KXM_ZARCH_AI_DATA_H_
#define KXM_ZARCH_AI_DATA_H_

namespace kxm {

namespace Game {
    template<class EventClass, class EventHandlerClass> class EventLoop;
}

namespace Zarch {
namespace AI {

//! AI data.
/*!
 *  \ingroup ZarchAI
 */
struct Data {
    Data() : updateDeltaTimeS(0.0f) {}
    float                                                          updateDeltaTimeS;
    std::shared_ptr<Game::EventLoop<ZarchEvent, EventHandlerCore>> eventLoop;
};

}    // Namespace AI.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_AI_DATA_H_
