//
//  NewLanderProcess.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#include <Zarch/Physics/LanderProcess.h>

#include <kxm/Core/NumberTools.h>
#include <Game/EventLoop.h>
#include <Zarch/MapParameters.h>
#include <Zarch/Terrain.h>
#include <Zarch/Events/MoveEvent.h>
#include <Zarch/Events/LanderVelocityEvent.h>
#include <Zarch/Events/LanderThrusterEvent.h>


using namespace std;
using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {
namespace Physics {

LanderProcess::LanderProcess(const shared_ptr<Physics::Data> &data)
        : data_(data),
          heading_(0.0f, 0.0f, -1.0f) {
}

void LanderProcess::Execute() {
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
    if (speedLength > 0.0f) {
        heading_ = (1.0f/speedLength) * speed;
    }
    NumberTools::Clamp(&speedLength, 0.0f, 1.0f);
    
    Vector up(0.0f, 1.0f, 0.0f);
    Transform newLanderTransform(CrossProduct(up, -heading_), up, -heading_);
    newLanderTransform.Prepend(Transform(XAxis, -speedLength * 120.0f));
    newLanderTransform.Prepend(Transform(YAxis, 180.0));
    
    // Apply gravity...
    data.landerState.velocity.y += data.updateDeltaTimeS * -data.mapParameters->gravity;
    // Apply thrust...?
    if (data.landerState.thrusterEnabled) {
        Vector thrustDirection(0.0f, 1.0f, 0.0f);
        newLanderTransform.ApplyTo(&thrustDirection);
        data.landerState.velocity += (  data.updateDeltaTimeS
                                        * data.mapParameters->landerThrust) * thrustDirection;
    }
    Vector position = data.landerState.transform.TranslationPart();
    position += data.updateDeltaTimeS * data.landerState.velocity;
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
    if (!data.landerActor.IsNone()) {
        std::printf("sending move, id=%d\n", data.landerActor.Id());
        data.eventLoop->Post(MoveEvent(data.landerActor, newLanderTransform));
    }
    data.eventLoop->Post(LanderVelocityEvent(data.landerState.velocity));
    if (data.landerState.thrusterEnabled != oldThrusterEnabled) {
        data.eventLoop->Post(LanderThrusterEvent(data.landerState.thrusterEnabled));
    }
}

bool LanderProcess::Finished() {
    return false;
}

}    // Namespace Physics.
}    // Namespace Zarch.
}    // Namespace kxm.
