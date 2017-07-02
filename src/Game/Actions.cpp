#include <kxm/Game/Actions.h>

#include <cstdio>

using namespace kxm::Core;

namespace kxm {
namespace Game {

int Actions::Register(ActionInterface *action) {
    int storageId;
    actions_.Get(0, &storageId) = action;
    return storageId;
}

void Actions::Unregister(int id) {
    actions_.Put(id);
}

void Actions::Execute() {
    int num = 0;
    for (ActionInterface *action : actions_.Iterate(0)) {
        action->ExecuteAction();
        ++num;
    }
    //std::printf("executed %d actions\n", num);
}

}    // Namespace Game.
}    // Namespace kxm.
