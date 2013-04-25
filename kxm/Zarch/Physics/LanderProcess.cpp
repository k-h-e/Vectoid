//
//  LanderProcess.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Zarch/Physics/LanderProcess.h>

#include <kxm/Core/NumberTools.h>
#include <kxm/Vectoid/Transform.h>
#include <kxm/Vectoid/CoordSysInterface.h>
#include <kxm/Game/EventQueue.h>
#include <kxm/Zarch/Terrain.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/ControlsState.h>

using boost::shared_ptr;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;
using namespace kxm::Zarch;


namespace kxm {
namespace Zarch {

LanderProcess::LanderProcess(shared_ptr<CoordSysInterface> landerCoordSys,
                             shared_ptr<const FrameTimeProcess::FrameTimeInfo> timeInfo,
                             shared_ptr<const ControlsState> controlsState,
                             shared_ptr<Terrain> terrain,
                             shared_ptr<const MapParameters> mapParameters)
        : landerCoordSys_(landerCoordSys),
          timeInfo_(timeInfo),
          controlsState_(controlsState),
          terrain_(terrain),
          mapParameters_(mapParameters),
          landerState_(new LanderStateInfo()),
          heading_(0.0f, 0.0f, -1.0f) {
}

shared_ptr<const LanderProcess::LanderStateInfo> LanderProcess::LanderState() {
    return landerState_;
}

bool LanderProcess::Execute(const Process::Context &context) {
    landerState_->thrusterEnabled = controlsState_->thrusterRequested;
    landerState_->firingEnabled   = controlsState_->firingRequested;
    
    float projection = controlsState_->orientationInput.x;
    NumberTools::Clamp(&projection, -1.0f, 1.0f);
    float xAngle = (float)asin(projection) * 180.0f / 3.141592654f;
    projection = controlsState_->orientationInput.y;
    NumberTools::Clamp(&projection, -1.0f, 1.0f);
    float yAngle = -(float)asin(projection) * 180.0f / 3.141592654f;
    float maxAngle = 30.0f;
    NumberTools::Clamp(&xAngle, -maxAngle, maxAngle);
    NumberTools::Clamp(&yAngle, -maxAngle, maxAngle);
    Vector speed(xAngle / maxAngle, 0.0f, yAngle / maxAngle);
    float  speedLength = speed.Length();
    if (speedLength > 0.0f)
        heading_ = (1.0f/speedLength) * speed;
    NumberTools::Clamp(&speedLength, 0.0f, 1.0f);
    
    Vector up(0.0f, 1.0f, 0.0f);
    Transform newLanderTransform(CrossProduct(up, -heading_), up, -heading_);
    newLanderTransform.Prepend(Transform(XAxis, -speedLength * 120.0f));
    newLanderTransform.Prepend(Transform(YAxis, 180.0));
    
    // Apply gravity...
    landerState_->velocity.y += timeInfo_->timeSinceLastFrame * -mapParameters_->gravity;
    // Apply thrust...?
    if (landerState_->thrusterEnabled) {
        Vector thrustDirection(0.0f, 1.0f, 0.0f);
        newLanderTransform.ApplyTo(&thrustDirection);
        landerState_->velocity += (  timeInfo_->timeSinceLastFrame
                                   * mapParameters_->landerThrust ) * thrustDirection;
    }
    Vector position = landerState_->transform.TranslationPart();
    position += timeInfo_->timeSinceLastFrame * landerState_->velocity;
    mapParameters_->xRange.ClampModulo(&position.x);
    mapParameters_->zRange.ClampModulo(&position.z);
    float terrainHeight = terrain_->Height(position.x, position.z);
    if (position.y < terrainHeight) {
        position.y               = terrainHeight;
        landerState_->velocity.y = 0.0f;
    }
    newLanderTransform.SetTranslationPart(position);
    
    landerCoordSys_->SetTransform(newLanderTransform);
    landerState_->transform = newLanderTransform;
    
    Event &event = static_cast<const ZarchProcess::Context &>(context).eventQueue.ScheduleEvent(
                       ZarchEvent::LanderMovedEvent);
    static_cast<TransformEvent &>(event).Reset(newLanderTransform);
        
    return true;
}

}    // Namespace Zarch.
}    // Namespace kxm.

