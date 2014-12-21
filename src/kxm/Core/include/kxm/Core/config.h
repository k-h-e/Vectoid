//
//  config.h
//  kxm
//
//  Created by Kai Hergenröther on 4/7/13.
//
//


#ifndef KXM_CORE_CONFIG_H_
#define KXM_CORE_CONFIG_H_


#include <stdint.h>


namespace kxm {
namespace Core {

//! Used for spacer data members guarding against the "neighboring field" multithreading issue.
typedef uint64_t spacer_t;

}
}


#endif    // KXM_CORE_CONFIG_H_
