//
//  events.h
//  kxm
//
//  Created by Kai Hergenröther on 11/30/12.
//
//


#ifndef KXM_ZARCH_EVENTS_H_
#define KXM_ZARCH_EVENTS_H_


#include <kxm/Vectoid/Transform.h>
#include <kxm/Game/Event.h>
#include <kxm/Zarch/ControlsState.h>


namespace kxm {
namespace Zarch {

class ZarchEvent : public Game::Event {
  public:
    enum EventType { FrameTimeEvent,
                     ControlsStateEvent,
                     LanderMovedEvent };
    EventType Type() const { return (EventType)type_; }
};

class ControlsStateEvent : public ZarchEvent {
  public:
    void Reset(const ControlsState &controlsState) { controlsState_ = controlsState; }
    const ControlsState &ControlsState() const { return controlsState_; }
  private:
    struct ControlsState controlsState_;
};

class TransformEvent : public ZarchEvent {
  public:
    void Reset(const Vectoid::Transform &transform) { transform_ = transform; }
    const Vectoid::Transform &Transform() const { return transform_; }
  private:
    Vectoid::Transform transform_;
};

class VariantEvent : public ZarchEvent {
  public:
    void Reset(int value)   { value_.intValue   = value; }
    void Reset(float value) { value_.floatValue = value; }
    int AsInt() const       { return value_.intValue;    }
    float AsFloat() const   { return value_.floatValue;  }
  private:
    union {
        int   intValue;
        float floatValue;
    } value_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_EVENTS_H_
