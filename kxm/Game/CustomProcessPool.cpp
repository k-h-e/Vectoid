//
//  CustomProcessPool.cpp
//  kxm
//
//  Created by Kai Hergenröther on 3/26/13.
//
//


#include <kxm/Game/CustomProcessPool.h>

using namespace boost;


namespace kxm {
namespace Game {

CustomProcessPool::CustomProcessPool()
        : processes_(1) {
}

Process &CustomProcessPool::Get(const shared_ptr<Process> &customProcess, int *id) {
    processes_.Get(0, id) = customProcess;
    return *customProcess;
}

Process &CustomProcessPool::Get(int *id) {
    assert (false);    // This method does not make sense with this pseudo pool!
    return Get(shared_ptr<Process>(), id);
}

Process &CustomProcessPool::Access(int id) {
    return *(processes_.Item(id));
}

void CustomProcessPool::Put(int id) {
    processes_.Item(id).reset();               
    processes_.Put(id);
}

}    // Namespace Game.
}    // Namespace kxm.
