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
    void Serialize(Core::Buffer *targetBuffer) {
        targetBuffer->Append(&type_, sizeof(type_));
        targetBuffer->Append(&controlsState_, sizeof(controlsState_));
    }
    void Deserialize(Core::Buffer::Reader *bufferReader) {
        bufferReader->ReadBlock(&controlsState_, sizeof(controlsState_));
    }
    bool DeserializeAndValidate(Core::Buffer::Reader *bufferReader) {
        return false;
    }
  private:
    struct ControlsState controlsState_;
};

class TransformEvent : public ZarchEvent {
  public:
    void Reset(const Vectoid::Transform &transform) { transform_ = transform; }
    const Vectoid::Transform &Transform() const { return transform_; }
    void Serialize(Core::Buffer *targetBuffer) {
        targetBuffer->Append(&type_, sizeof(type_));
        targetBuffer->Append(&transform_, sizeof(transform_));
    }
    void Deserialize(Core::Buffer::Reader *bufferReader) {
        bufferReader->ReadBlock(&transform_, sizeof(transform_));
    }
    bool DeserializeAndValidate(Core::Buffer::Reader *bufferReader) {
        return false;
    }
  private:
    Vectoid::Transform transform_;
};

class VariantEvent : public ZarchEvent {
  public:
    void Reset(int value)   { value_.intValue   = value; }
    void Reset(float value) { value_.floatValue = value; }
    int AsInt() const       { return value_.intValue;    }
    float AsFloat() const   { return value_.floatValue;  }
    void Serialize(Core::Buffer *targetBuffer) {
        targetBuffer->Append(&type_, sizeof(type_));
        targetBuffer->Append(&value_, sizeof(value_));
    }
    void Deserialize(Core::Buffer::Reader *bufferReader) {
        bufferReader->ReadBlock(&value_, sizeof(value_));
    }
    bool DeserializeAndValidate(Core::Buffer::Reader *bufferReader) {
        return false;
    }
  private:
    union {
        int   intValue;
        float floatValue;
    } value_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_EVENTS_H_
