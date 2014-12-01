//
//  ZarchEvent.h
//  kxm
//
//  Created by Kai Hergenröther on 10/29/14.
//
//


#ifndef KXM_ZARCH_ZARCHEVENT_H_
#define KXM_ZARCH_ZARCHEVENT_H_


#include <kxm/Game/Event.h>


namespace kxm {
namespace Zarch {

class Video;
class Physics;
class GameLogic;

class ZarchEvent : public Game::Event {
  public:
    virtual void DispatchToVideo(Video *video) const;
    virtual void DispatchToPhysics(Physics *physics) const;
    virtual void DispatchToGameLogic(GameLogic *gameLogic) const;
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_ZARCHEVENT_H_

