#ifndef KXM_GAME_NETWORKEVENTCOUPLING_READER_H_
#define KXM_GAME_NETWORKEVENTCOUPLING_READER_H_

#include <kxm/Game/NetworkEventCoupling.h>

namespace kxm {
namespace Game {

class EventLoopHub;

//! Reader for the network event coupling.
/*!
 *  \ingroup Game
 */
class NetworkEventCoupling::Reader {
  public:
    Reader(const std::shared_ptr<kxm::Game::EventLoopHub> &hub, std::shared_ptr<SharedState> sharedState);
    void Run();

  private:
    std::shared_ptr<SharedState>             sharedState_;
    std::shared_ptr<kxm::Game::EventLoopHub> hub_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_NETWORKEVENTCOUPLING_READER_H_
