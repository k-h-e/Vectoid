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
#include <kxm/Game/OldEvent.h>


namespace kxm {
namespace Zarch {

class OldZarchEvent : public Game::OldEvent {
  public:
    enum EventType { FrameTimeEvent     = 0,
                     ControlsStateEvent,
                     LanderMoveEvent,
                     LanderVelocityEvent,
                     LanderThrusterEvent };
    EventType Type() const { return (EventType)type_; }
};

class Variant {
  public:
    void Reset(int value)   { value_.intValue   = value; }
    void Reset(float value) { value_.floatValue = value; }
    void Reset(bool value)  { value_.boolValue  = value; }
    int AsInt() const       { return value_.intValue;    }
    float AsFloat() const   { return value_.floatValue;  }
    bool AsBool() const     { return value_.boolValue;   }
  
  private:
    union {
        int   intValue;
        float floatValue;
        bool  boolValue;
    } value_;
};

template<class T> class OldEvent : public OldZarchEvent {
  public:
    void Reset(const T &data) { data_ = data; }
    const T &Data() const     { return data_; }
    T &Data()                 { return data_; }
    void Serialize(Core::Buffer *targetBuffer) {
        targetBuffer->Append(&type_, sizeof(type_));
        targetBuffer->Append(&data_, sizeof(data_));
    }
    void Deserialize(Core::Buffer::Reader *bufferReader) {
        bufferReader->ReadBlock(&data_, sizeof(data_));
    }
    bool DeserializeAndValidate(Core::Buffer::Reader *bufferReader) {
        return false;
    }
  private:
    T data_;
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_EVENTS_H_
