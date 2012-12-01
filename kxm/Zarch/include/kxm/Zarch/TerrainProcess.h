//
//  TerrainProcess.h
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_TERRAINPROCESS_H_
#define KXM_ZARCH_TERRAINPROCESS_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Zarch/LanderProcess.h>


namespace kxm {

namespace Vectoid {
    class Transform;
}

namespace Zarch {

class TerrainRenderer;

//! Keeps the terrain in sync with the lander position.
/*!
 *  \ingroup Zarch
 */
class TerrainProcess : public Game::Process {
  public:
    TerrainProcess(boost::shared_ptr<TerrainRenderer> terrainRenderer,
                   boost::shared_ptr<const LanderProcess::LanderStateInfo> landerState);
    
    bool Execute();
    
  private:
    TerrainProcess(const TerrainProcess &other);
    TerrainProcess &operator=(const TerrainProcess &other);
    
    boost::shared_ptr<TerrainRenderer>                      terrainRenderer_;
    boost::shared_ptr<const LanderProcess::LanderStateInfo> landerState_;
};

}    // Namespace Zarch
}    // Namespace kxm.


#endif    // KXM_ZARCH_TERRAINPROCESS_H_
