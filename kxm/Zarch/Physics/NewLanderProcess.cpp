//
//  NewLanderProcess.cpp
//  kxm
//
//  Created by Kai Hergenröther on 4/28/13.
//
//


#include <kxm/Zarch/Physics/NewLanderProcess.h>

#include <kxm/Core/NumberTools.h>
#include <kxm/Game/EventQueue.h>
#include <kxm/Zarch/MapParameters.h>
#include <kxm/Zarch/Terrain.h>


using namespace kxm::Core;
using namespace kxm::Vectoid;
using namespace kxm::Game;


namespace kxm {
namespace Zarch {

NewLanderProcess::NewLanderProcess(const boost::shared_ptr<NewPhysics::Data> &data)
        : data_(data),
          heading_(0.0f, 0.0f, -1.0f) {
}

bool NewLanderProcess::Execute(const Process::Context &context) {
    data_->landerState.thrusterEnabled = data_->controlsState.thrusterRequested;
    data_->landerState.firingEnabled   = data_->controlsState.firingRequested;
    
    float projection = data_->controlsState.orientationInput.x;
    NumberTools::Clamp(&projection, -1.0f, 1.0f);
    float xAngle = (float)asin(projection) * 180.0f / 3.141592654f;
    projection = data_->controlsState.orientationInput.y;
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
    data_->landerState.velocity.y += data_->frameDeltaTimeS * -data_->mapParameters->gravity;
    // Apply thrust...?
    if (data_->landerState.thrusterEnabled) {
        Vector thrustDirection(0.0f, 1.0f, 0.0f);
        newLanderTransform.ApplyTo(&thrustDirection);
        data_->landerState.velocity += (  data_->frameDeltaTimeS
                                        * data_->mapParameters->landerThrust) * thrustDirection;
    }
    Vector position = data_->landerState.transform.TranslationPart();
    position += data_->frameDeltaTimeS * data_->landerState.velocity;
    data_->mapParameters->xRange.ClampModulo(&position.x);
    data_->mapParameters->zRange.ClampModulo(&position.z);
    float terrainHeight = data_->terrain->Height(position.x, position.z);
    if (position.y < terrainHeight) {
        position.y                    = terrainHeight;
        data_->landerState.velocity.y = 0.0f;
    }
    newLanderTransform.SetTranslationPart(position);
    
    data_->landerState.transform = newLanderTransform;
    Event &event = static_cast<const ZarchProcess::Context &>(context).eventQueue.ScheduleEvent(
                       ZarchEvent::LanderMovedEvent);
    static_cast<TransformEvent &>(event).Reset(newLanderTransform);
    return true;
}

}    // Namespace Zarch.
}    // Namespace kxm.
