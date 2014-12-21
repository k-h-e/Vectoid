//
//  Process.h
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_GAME_CUSTOMPROCESSPOOL_H_
#define KXM_GAME_CUSTOMPROCESSPOOL_H_


#include <memory>

#include <kxm/Core/ReusableItems.h>
#include <Game/PoolInterface.h>


namespace kxm {
namespace Game {

class Process;

//! Pseudo-pool managing custom processes within the \ref Processes scheme.
/*!
 *  \ingroup Game.
 */
class CustomProcessPool : public virtual PoolInterface<Process> {
  public:
    CustomProcessPool();
    Process &Get(const std::shared_ptr<Process> &customProcess, int *id);
    Process &Get(int *id);
    Process &Access(int id);
    void Put(int id);
    
  private:
    CustomProcessPool(const CustomProcessPool &other);
    CustomProcessPool &operator=(const CustomProcessPool &other);
    
    Core::ReusableItems<std::shared_ptr<Process>> processes_;
};

}    // Namespace Game.
}    // Namespace kxm.


#endif    // KXM_GAME_CUSTOMPROCESSPOOL_H_
