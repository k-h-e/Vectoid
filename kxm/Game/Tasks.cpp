//
//  Tasks.cpp
//  kxm
//
//  Created by Kai Hergenröther on 10/7/12.
//
//


#include <kxm/Game/Tasks.h>

#include <kxm/Core/logging.h>

using namespace std;
using boost::shared_ptr;
using namespace kxm::Core;


namespace kxm {
namespace Game {

Tasks::Tasks() {
    activeTasksGroup_ = tasks_.AddGroup();
    addedTasksGroup_  = tasks_.AddGroup();
}

TaskInterface *Tasks::AddTask(int reuseGroup) {
    ItemGroups<shared_ptr<TaskInterface> >::Iterator
        iterator = tasks_.GetIterator(reuseGroup);
    shared_ptr<TaskInterface> *taskHandlePointer = iterator.GetNext();
    if (taskHandlePointer) {
        iterator.MoveTo(addedTasksGroup_);
        return &**taskHandlePointer;
    }
    else {
        return 0;
    }
}

TaskInterface *Tasks::AddTask(shared_ptr<TaskInterface> task, int reuseGroup) {
    task->SetReuseGroup(reuseGroup);
    shared_ptr<TaskInterface> *taskHandlePointer = tasks_.AddItem(addedTasksGroup_);
    *taskHandlePointer = task;
    return &*task;
}

void Tasks::Execute() {
    // Activate new tasks that have recently been added...
    int numActivated = 0;
    ItemGroups<shared_ptr<TaskInterface> >::Iterator
        iterator = tasks_.GetIterator(addedTasksGroup_);
    while (iterator.GetNext()) {
        iterator.MoveTo(activeTasksGroup_);
        ++numActivated;
    }
    if (numActivated)
        Log(this).Stream() << "activated " << numActivated << " new tasks" << endl;
    
    // Execute the active tasks...
    shared_ptr<TaskInterface> *taskHandlePointer;
    int numReused  = 0,
        numDeleted = 0;
    iterator = tasks_.GetIterator(activeTasksGroup_);
    while ((taskHandlePointer = iterator.GetNext())) {
        if (!(*taskHandlePointer)->Execute()) {    // Task has finished.
            int reuseGroup = (*taskHandlePointer)->ReuseGroup();
            if (reuseGroup >= 0) {
                iterator.MoveTo(reuseGroup);
                ++numReused;
            }
            else {
                (*taskHandlePointer).reset();
                iterator.MoveToIdle();
                ++numDeleted;
            }
        }
    }
    if (numReused + numDeleted)
        Log(this).Stream() << (numReused + numDeleted) << " jobs finished"
                           << ", num_kept_for_reuse=" << numReused
                           << ", num_deleted=" << numDeleted << endl;
}

}    // Namespace Game.
}    // Namespace kxm.
