#ifndef KXM_ZARCH_PLAYERSTATSEVENT_H_
#define KXM_ZARCH_PLAYERSTATSEVENT_H_

#include <kxm/Game/ActorName.h>
#include <kxm/Zarch/Events/ZarchEvent.h>

namespace kxm {
namespace Zarch {

//! Transports player stats.
/*!
 *  \ingroup ZarchEvents
 */
class PlayerStatsEvent : public ZarchEvent {
  public:
    static const EventType type;
    static const int statMaxCount = 4;
    
    enum StatType { FuelStat,
                    MaxFuelStat };
    
    struct Stat {
        StatType type;
        int      value;
        Stat(StatType aType, int aValue) : type(aType), value(aValue) {}
        Stat() : type(MaxFuelStat), value(0) {}
        // Default copy/move okay.
    };
  
    PlayerStatsEvent();
    PlayerStatsEvent(const Game::ActorName &actor);
    //! Gets the number of stats stored in the event.
    int StatCount() const;
    //! Adds a stat of specified type and value.
    void AddStat(StatType type, int value);
    //! Retrieves the stat with specified index.
    void GetStat(int index, Stat *outStat) const;
    const EventType &Type() const { return type; }
    void Serialize(Core::Buffer *targetBuffer) const;
    void Deserialize(Core::Buffer::Reader *bufferReader);
    void Dispatch(EventHandlerCore *handler) const;
    
    Game::ActorName actor;
    
  private:
    int  statCount_;
    Stat stats_[statMaxCount];
};

}    // Namespace Zarch.
}    // Namespace kxm.

#endif    // KXM_ZARCH_PLAYERSTATSEVENT_H_
