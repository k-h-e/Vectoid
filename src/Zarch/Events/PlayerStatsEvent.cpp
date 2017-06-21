#include <kxm/Zarch/Events/PlayerStatsEvent.h>

#include <assert.h>
#include <kxm/Zarch/EventHandlerCore.h>

using namespace kxm::Game;

namespace kxm {
namespace Zarch {

const Game::Event::EventType PlayerStatsEvent::type("PlayerStatsEvent");

PlayerStatsEvent::PlayerStatsEvent()
    : statCount_(0) {
    // Nop.
}

PlayerStatsEvent::PlayerStatsEvent(const ActorName &name)
    : actor(name),
      statCount_(0) {
    // Nop.
}

int PlayerStatsEvent::StatCount() const {
    return statCount_;
}

void PlayerStatsEvent::AddStat(StatType type, int value) {
    assert(statCount_ < statMaxCount);
    stats_[statCount_] = Stat(type, value);
    ++statCount_;
}

void PlayerStatsEvent::GetStat(int index, Stat *outStat) const {
    assert((index >= 0) && (index < statCount_));
    *outStat = stats_[index];
}

void PlayerStatsEvent::Serialize(Core::Buffer *targetBuffer) const {
    targetBuffer->Append(&actor, sizeof(actor));
    targetBuffer->Append(&statCount_, sizeof(statCount_));
    for (int i = 0; i < statCount_; ++i) {
        targetBuffer->Append(&stats_[i], sizeof(Stat));
    }
}

void PlayerStatsEvent::Deserialize(Core::Buffer::Reader *bufferReader) {
    bufferReader->ReadBlock(&actor, sizeof(actor));
    bufferReader->ReadBlock(&statCount_, sizeof(statCount_));
    for (int i = 0; i < statCount_; ++i) {
        bufferReader->ReadBlock(&stats_[i], sizeof(Stat));
    }
}

void PlayerStatsEvent::Dispatch(EventHandlerCore *handler) const {
    handler->Handle(*this);
}

}    // Namespace Zarch.
}    // Namespace kxm.
