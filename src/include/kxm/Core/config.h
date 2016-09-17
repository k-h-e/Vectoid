#ifndef KXM_CORE_CONFIG_H_
#define KXM_CORE_CONFIG_H_

#include <stdint.h>

namespace kxm {
namespace Core {

//! Used for spacer data members guarding against the "neighboring field" multithreading issue.
typedef uint64_t spacer_t;

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_CONFIG_H_
