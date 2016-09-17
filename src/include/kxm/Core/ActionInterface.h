#ifndef KXM_CORE_ACTIONINTERFACE_H_
#define KXM_CORE_ACTIONINTERFACE_H_

#include <kxm/Core/Interface.h>

namespace kxm {
namespace Core {

//! Interface to actions that can be executed.
/*!
 *  \ingroup Core
 */
class ActionInterface : public virtual Interface {
  public:
    //! Executes the action.
    virtual void ExecuteAction() = 0;
};

}
}

#endif    // KXM_CORE_ACTIONINTERFACE_H_
