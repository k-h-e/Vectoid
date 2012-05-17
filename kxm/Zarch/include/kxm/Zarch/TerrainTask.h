//
//  TerrainTask.h
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_TERRAINTASK_H_
#define KXM_ZARCH_TERRAINTASK_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Game/TaskInterface.h>
#include <kxm/Zarch/LanderTask.h>


namespace kxm {

namespace Vectoid {
    class Transform;
}

namespace Zarch {

class ZarchTerrain;

//! Keeps the terrain in sync with the lander position.
/*!
 *  \ingroup Zarch
 */
class TerrainTask : public virtual Game::TaskInterface {
  public:
    TerrainTask(boost::shared_ptr<ZarchTerrain> terrain,
                boost::shared_ptr<const LanderTask::LanderStateInfo> landerState);
    
    void Execute();
    
  private:
    TerrainTask(const TerrainTask &other);
    TerrainTask &operator=(const TerrainTask &other);
    
    boost::shared_ptr<ZarchTerrain>                      terrain_;
    boost::shared_ptr<const LanderTask::LanderStateInfo> landerState_;
};


}    // Namespace Zarch
}    // Namespace kxm.


#endif    // KXM_ZARCH_TERRAINTASK_H_
