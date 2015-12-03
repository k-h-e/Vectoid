#include <Game/Processes.h>


namespace kxm {
namespace Game {

Processes::Processes()
        : processes_(1),
          numProcesses_(0) {
    // Nop.
}
    
void Processes::ExecuteProcesses() {
}
    
int Processes::Count() {
    return numProcesses_;
}

}    // Namespace Game.
}    // Namespace kxm.
