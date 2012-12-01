//
//  processes.h
//  kxm
//
//  Created by Kai Hergenröther on 12/1/12.
//
//


#ifndef KXM_ZARCH_PROCESSES_H_
#define KXM_ZARCH_PROCESSES_H_


#include <kxm/Game/Process.h>


namespace kxm {
namespace Zarch {

class ZarchProcess : public Game::Process {
  public:
    enum Type { SeederProcess };
};

class SeederProcess : public ZarchProcess {
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif
