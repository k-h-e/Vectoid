//
//  Task.h
//  kxm
//
//  Created by Kai Hergenröther on 10/7/12.
//
//


#ifndef KXM_GAME_TASK_H_
#define KXM_GAME_TASK_H_


#include <kxm/Game/TaskInterface.h>


namespace kxm {
namespace Game {

//! Provides functionality common to TaskInterface implementations.
/*!
 *  \ingroup Game
 */
class Task : public TaskInterface {
  public:
    Task();
    int ReuseGroup();
    void SetReuseGroup(int reuseGroup);
    
  private:
    int reuseGroup_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_TASK_H_
