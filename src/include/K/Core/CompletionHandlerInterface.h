#ifndef K_CORE_COMPLETIONHANDLERINTERFACE_H_
#define K_CORE_COMPLETIONHANDLERINTERFACE_H_

#include <kxm/Core/Interface.h>

namespace K {
namespace Core {

//! Interface to completion handlers.
/*!
 *  \ingroup Core
 */
class CompletionHandlerInterface : public virtual kxm::Core::Interface {
  public:
    //! Called upon completion of the specified operation.
    virtual void OnCompletion(int operationId) = 0;
};

}    // Namespace Core.
}    // Namespace K.

#endif    // K_CORE_COMPLETIONHANDLERINTERFACE_H_
