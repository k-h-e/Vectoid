#ifndef KXM_GAME_ACTIONS_H_
#define KXM_GAME_ACTIONS_H_

#include <kxm/Core/ReusableItems.h>
#include <kxm/Core/ActionInterface.h>

namespace kxm {
namespace Game {

//! Keeps track of actions to perform.
/*!
 *  \ingroup Game
 */
class Actions {
  public:
    Actions() : actions_(1) {};
    Actions(const Actions &other)            = delete;
    Actions &operator=(const Actions &other) = delete;
    Actions(Actions &&other)                 = delete;
    Actions &operator=(Actions &&other)      = delete;
    //! Registers the specified action as weak reference (dumb pointer), and returns a non-negative id for unregistering
    //! it later.
    int Register(Core::ActionInterface *action);
    //! Unregisters the specified action.
    void Unregister(int id);
    //! Executes the registered actions, once each.
    void Execute();
    
  private:
    Core::ReusableItems<Core::ActionInterface *> actions_;
};

}    // Namespace Game.
}    // Namespace kxm.

#endif    // KXM_GAME_ACTIONS_H_
