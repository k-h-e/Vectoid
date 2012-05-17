//
//  TerrainTask.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/TerrainTask.h>

#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/ZarchTerrain.h>

using boost::shared_ptr;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

TerrainTask::TerrainTask(shared_ptr<ZarchTerrain> terrain,
                         shared_ptr<const LanderTask::LanderStateInfo> landerState)
    : terrain_(terrain),
      landerState_(landerState) {
}

void TerrainTask::Execute() {
    Vector position = landerState_->transform.TranslationPart();
    terrain_->SetObserverPosition(position.x, position.z);
}


}    // Namespace Zarch.
}    // Namespace kxm.
