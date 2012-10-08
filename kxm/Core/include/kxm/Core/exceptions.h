//
//  exceptions.h
//  kxm
//
//  Created by Kai Hergenröther on 10/8/12.
//
//


#ifndef KXM_CORE_EXCEPTIONS_H_
#define KXM_CORE_EXCEPTIONS_H_


#include <exception>


namespace kxm {
namespace Core {

//! Base class to <c>kxm</c> exceptions. <b>[Read on!]</b>
/*! 
 *  \ingroup Core
 *
 *  Currently, <c>kxm</c> uses exceptions only to react to programmer error. Note furthermore that
 *  <b>currently, <c>kxm</c> is not generally exception-safe, and that an application should be
 *  terminated shortly after catching an exception that may have been thrown in and/or propagated
 *  through <c>kxm</c> code.</b>
 */
class Exception : std::exception {
};

//! \ref Exception thrown in case bad arguments (parameters) have been passed to a method.
/*!
 *  \ingroup Core
 */
class BadArgumentException : public virtual Exception {
};

//! \ref Exception thrown in case an operation has been attempted that is unavailable.
/*!
 *  \ingroup Core
 */
class OperationUnavailableException : public virtual Exception {
};


}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_EXCEPTIONS_H_
