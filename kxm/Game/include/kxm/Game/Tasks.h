//
//  Tasks.h
//  kxm
//
//  Created by Kai Hergenröther on 10/7/12.
//
//


#ifndef KXM_GAME_TASKS_
#define KXM_GAME_TASKS_


#include <boost/shared_ptr.hpp>

#include <kxm/Core/ItemGroups.h>
#include <kxm/Game/TaskInterface.h>


namespace kxm {
namespace Game {

//! Manages a collection of tasks (\ref TaskInterface instances) in order to execute them using a
//! co-operative scheduling scheme.
/*!
 *  \ingroup Game
 */
class Tasks : public Core::Interface {
  public:
    Tasks();
    
    //! <b>[Can safely be called from tasks currently \ref Execute() ed by the \ref Tasks
    //! collection]</b> Adds a new task by taking one from the specified re-use group, and provides
    //! access to it.
    /*!
     *  The task is not immediately called - it is only put into a special "added tasks" group from
     *  where it will be fetched and made active upon the next call to \ref Execute(). Typically,
     *  the calling context will want to re-initialize the task object berfore that happens.
     *
     *  \return
     *  <c>0</c> in case there is no task object available for re-use.
     */
    TaskInterface *AddTask(int reuseGroup);
    
    //! <b>[Can safely be called from tasks currently \ref Execute() ed by the \ref Tasks
    //! collection]</b> Adds the specified new task object to the tasks collection.
    /*!
     *  \param reuseGroup
     *  If you want the task object to be re-used after the task has finished, specify here the
     *  appropriate re-use group. Otherwise say <c>TaskInterface::NoReuseGroup</c>
     *
     *  \return
     *  Dumb pointer to the added task object, for convenience.
     */
    TaskInterface *AddTask(boost::shared_ptr<TaskInterface> task, int reuseGroup);
    
    //! Executes each of the active tasks in the collection.
    /*!
     *  Before executing the first task, all new tasks that have recently been added via AddTask()
     *  are made active.
     *
     *  Tasks that indicate that they have finished get automatically deregistered. In case a task
     *  indicates a re-use group, it is moved to that group for later re-use. Otherwise, the task
     *  object gets discarded.
     */
    void Execute();
    
  private:
    Tasks(const Tasks &other);
    Tasks &operator=(const Tasks &other);
    
    Core::ItemGroups<boost::shared_ptr<TaskInterface> > tasks_;
    int                                                 activeTasksGroup_,
                                                        addedTasksGroup_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_TASKS_
