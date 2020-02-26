#ifndef K_CORE_COMPLETIONNOTIFIERINTERFACE_H_
#define K_CORE_COMPLETIONNOTIFIERINTERFACE_H_

#include <kxm/Core/Interface.h>

namespace K {
namespace Core {

class CompletionHandlerInterface;

//! Interface to entities notifying completion of an operation.
/*!
 *  \ingroup Core
 */
class CompletionNotifierInterface : public virtual kxm::Core::Interface {
  public:
    //! Registers the specified completion handler for an operation that is clear from context.
    /*!
     *  When the respective operation completes, the handler's <c>OnCompletion()</c> method will get invoked on an
     *  arbitrary thread, with the specified operation id as argument. The handler's <c>OnCompletion()</c> method will
     *  get called once at most. It is safe to delete the handler after that has happened.
     *
     *  The handler is expected to live until either it is called upon completion of the respective operation or it is
     *  unregistered again.
     */
    virtual void RegisterCompletionHandler(CompletionHandlerInterface &handler, int operationId) = 0;
    //! Unregisters the specified completion handler if it is registered.
    /*!
     *  It is safe to delete the handler once this method has returned.
     */
    virtual void UnregisterCompletionHandler(CompletionHandlerInterface &handler) = 0;
};

}    // Namespace Core.
}    // Namespace K.

#endif    // K_CORE_COMPLETIONNOTIFIERINTERFACE_H_
