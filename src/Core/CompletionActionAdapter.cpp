#include <K/Core/CompletionActionAdapter.h>

#include <kxm/Core/ActionInterface.h>

using std::shared_ptr;
using kxm::Core::ActionInterface;

namespace K {
namespace Core {

CompletionActionAdapter::CompletionActionAdapter(const shared_ptr<ActionInterface> &action)
        : action_(action) {
    // Nop.
}

void CompletionActionAdapter::OnCompletion(int completionId) {
    (void)completionId;
    action_->ExecuteAction();
}

}    // Namespace Core.
}    // Namespace K.
