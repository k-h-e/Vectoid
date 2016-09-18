#ifndef KXM_ZARCH_VIDEO_SHOT_H_
#define KXM_ZARCH_VIDEO_SHOT_H_

#include <kxm/Zarch/Video/Actor.h>

namespace kxm {
namespace Zarch {

class ActorCreationEvent;
class ActorTerminationEvent;
class MoveEvent;

namespace Video {

struct Data;

//! Represents a shot inside the video sub system.
/*!
 *  \ingroup ZarchVideo
 */
class Shot : public Actor {
  public:
    Shot();
    Shot(const Shot &other)            = delete;
    Shot &operator=(const Shot &other) = delete;
    Shot(const Shot &&other)           = delete;
    Shot &operator=(Shot &&other)      = delete;
    void Handle(const ActorCreationEvent &event);
    void Handle(const ActorTerminationEvent &event);
    void Handle(const MoveEvent &event);
    void ExecuteAction();
    
  private:
    int particleStorageId_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_SHOT_H_
