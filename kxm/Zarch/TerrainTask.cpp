//
//  TerrainTask.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/TerrainTask.h>

#include <kxm/Vectoid/Transform.h>
#include <kxm/Zarch/TerrainRenderer.h>

using boost::shared_ptr;
using namespace kxm::Vectoid;


namespace kxm {
namespace Zarch {

TerrainTask::TerrainTask(shared_ptr<TerrainRenderer> terrainRenderer,
                         shared_ptr<const LanderTask::LanderStateInfo> landerState)
    : terrainRenderer_(terrainRenderer),
      landerState_(landerState) {
}

bool TerrainTask::Execute() {
    Vector position = landerState_->transform.TranslationPart();
    terrainRenderer_->SetObserverPosition(position.x, position.z);
    return true;
}

}    // Namespace Zarch.
}    // Namespace kxm.
