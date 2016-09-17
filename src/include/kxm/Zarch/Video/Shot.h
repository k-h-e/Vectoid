#ifndef KXM_ZARCH_VIDEO_SHOT_H_
#define KXM_ZARCH_VIDEO_SHOT_H_

#include <memory>
#include <kxm/Core/ActionInterface.h>
#include <kxm/Zarch/EventHandlerCore.h>

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
class Shot : public EventHandlerCore, public virtual Core::ActionInterface {
  public:
    Shot();
    Shot(const Shot &other)            = delete;
    Shot &operator=(const Shot &other) = delete;
    Shot(const Shot &&other)           = delete;
    Shot &operator=(Shot &&other)      = delete;
    void Reset(const std::shared_ptr<Data> &data);
    void Handle(const ActorCreationEvent &event);
    void Handle(const ActorTerminationEvent &event);
    void Handle(const MoveEvent &event);
    void ExecuteAction();
    
  private:
    std::shared_ptr<Data> data_;    // Null when default-initialized!
    int                   particleStorageId_;
};

}    // Namespace Video.
}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_VIDEO_SHOT_H_
