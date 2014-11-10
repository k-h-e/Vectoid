//
//  NewLanderProcess.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#include <kxm/Zarch/Physics/LanderProcess.h>

#include <kxm/Core/NumberTools.h>
#include <kxm/Game/OldEventQueue.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>


using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

LanderProcess::LanderProcess(const shared_ptr<Physics::Data> &data)
        : data_(data),
          heading_(0.0f, 0.0f, -1.0f) {
}

bool LanderProcess::Execute(const ExecutionContext &context) {
    Physics::Data &data = *data_;
    
    bool oldThrusterEnabled = data.landerState.thrusterEnabled;
    data.landerState.thrusterEnabled = data.controlsState.thrusterRequested;
    data.landerState.firingEnabled   = data.controlsState.firingRequested;
    
    float projection = data.controlsState.orientationInput.x;
    NumberTools::Clamp(&projection, -1.0f, 1.0f);
    float xAngle = (float)asin(projection) * 180.0f / NumberTools::piAsFloat;
    projection = data.controlsState.orientationInput.y;
    NumberTools::Clamp(&projection, -1.0f, 1.0f);
    float yAngle = -(float)asin(projection) * 180.0f / NumberTools::piAsFloat;
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
    data.landerState.velocity.y += data.frameDeltaTimeS * -data.mapParameters->gravity;
    // Apply thrust...?
    if (data.landerState.thrusterEnabled) {
        Vector thrustDirection(0.0f, 1.0f, 0.0f);
        newLanderTransform.ApplyTo(&thrustDirection);
        data.landerState.velocity += (  data.frameDeltaTimeS
                                        * data.mapParameters->landerThrust) * thrustDirection;
    }
    Vector position = data.landerState.transform.TranslationPart();
    position += data.frameDeltaTimeS * data.landerState.velocity;
    data.mapParameters->xRange.ClampModulo(&position.x);
    data.mapParameters->zRange.ClampModulo(&position.z);
    float terrainHeight = data.terrain->Height(position.x, position.z);
    if (position.y < terrainHeight) {
        position.y                  = terrainHeight;
        data.landerState.velocity.y = 0.0f;
    }
    newLanderTransform.SetTranslationPart(position);
    data.landerState.transform = newLanderTransform;
    
    // Generate events...
    auto &eventQueue = static_cast<const ZarchProcess::Context &>(context).eventQueue;
    eventQueue.ScheduleEvent<OldEvent<Transform>>(OldZarchEvent::LanderMoveEvent)
              .Reset(newLanderTransform);
    eventQueue.ScheduleEvent<OldEvent<Vector>>(OldZarchEvent::LanderVelocityEvent)
              .Reset(data.landerState.velocity);
    if (data.landerState.thrusterEnabled != oldThrusterEnabled) {
        eventQueue.ScheduleEvent<OldEvent<Variant>>(OldZarchEvent::LanderThrusterEvent).Data()
                  .Reset(data.landerState.thrusterEnabled);
    }
    
    return true;
}

}    // Namespace Zarch.
}    // Namespace kxm.