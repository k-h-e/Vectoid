//
//  terminal.h
//  kxm
//
//  Created by Kai Hergenröther on 3/30/13.
//
//


#ifndef KXM_CORE_TERMINAL_H_
#define KXM_CORE_TERMINAL_H_


#include <cstdlib>

#include <string>


namespace kxm {
namespace Core {

//! Central place to handle a terminal error condition.
inline void HandleTerminalCondition(const std::string &message) {
    std::printf("*** terminal condition: %s\n", message.c_str());
    std::exit(1);
}

}    // Namespace Core.
}    // Namespace kxm.


#endif    // KXM_CORE_TERMINAL_H_
