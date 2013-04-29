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
#include <kxm/Zarch/events.h>

namespace kxm {

namespace Game {
    template<class T> class EventQueue;
    template<class T> class Processes;
}

namespace Zarch {

class ZarchProcess : public Game::Process {
  public:
    enum ProcessType { SeederProcess = 0 };
    struct Context : public Process::Context {
        Context(
            Game::Processes<ProcessType> &aProcessesSet,
            Game::EventQueue<ZarchEvent::EventType> &anEventQueue)
                : processes(aProcessesSet),
                  eventQueue(anEventQueue) {
        }
        Game::Processes<ProcessType>            &processes;
        Game::EventQueue<ZarchEvent::EventType> &eventQueue;
    };
};

class SeederProcess : public ZarchProcess {
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif
