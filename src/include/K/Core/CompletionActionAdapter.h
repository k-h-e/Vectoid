#ifndef K_CORE_COMPLETIONACTIONADAPTER_H_
#define K_CORE_COMPLETIONACTIONADAPTER_H_

#include <memory>
#include <K/Core/CompletionHandlerInterface.h>

namespace kxm {
namespace Core {
    class ActionInterface;
}
}

namespace K {
namespace Core {

//! Completion handler executing an action.
/*!
 *  \ingroup Core
 */
class CompletionActionAdapter : public virtual CompletionHandlerInterface {
  public:
    CompletionActionAdapter(const std::shared_ptr<kxm::Core::ActionInterface> &action);
    virtual void OnCompletion(int completionId);

  private:
    std::shared_ptr<kxm::Core::ActionInterface> action_;
};

}    // Namespace Core.
}    // Namespace K.

#endif    // K_CORE_COMPLETIONACTIONADAPTER_H_
