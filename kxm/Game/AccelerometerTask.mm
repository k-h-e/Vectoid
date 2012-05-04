//
//  AccelerometerTask.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Game/AccelerometerTask.h>

#include <kxm/Vectoid/Vector.h>
#include <kxm/Vectoid/Transform.h>

#import <CoreMotion/CMMotionManager.h>

using boost::shared_ptr;
using namespace kxm::Vectoid;


namespace kxm {
namespace Game {

AccelerometerTask::AccelerometerTask()
        : acceleration_(new Vector()),
          calibrationAngle_(40.0f),
          panningOverrideEnabled_(false) {
    CMMotionManager *manager = [[CMMotionManager alloc] init];
    [manager retain];
    [manager startDeviceMotionUpdates];
    motionManager_ = manager;
}

AccelerometerTask::~AccelerometerTask() {
    CMMotionManager *manager = (CMMotionManager *)motionManager_;
    [manager stopDeviceMotionUpdates];
    [manager release];
}

shared_ptr<const Vector> AccelerometerTask::Acceleration() const {
    return acceleration_;
}

void AccelerometerTask::BeginPanningOverride() {
    panningOverrideX_       = 0.0f;
    panningOverrideY_       = 0.0f;
    panningOverrideEnabled_ = true;
    std::puts("panning override on");
}

void AccelerometerTask::UpdatePanningOverride(float x, float y) {
    panningOverrideX_ = x;
    panningOverrideY_ = y;
}

void AccelerometerTask::EndPanningOverride() {
    panningOverrideEnabled_ = false;
    std::puts("panning override off");
}

void AccelerometerTask::Execute() {
    Vector gravity;
    if (panningOverrideEnabled_) {
        gravity = Vector(panningOverrideX_, -panningOverrideY_, -200.0f);
        gravity.TryNormalize();
    }
    else {
        CMAcceleration acceleration = ((CMMotionManager *)motionManager_).deviceMotion.gravity;
        gravity = Vector(acceleration.x, acceleration.y, acceleration.z);
        Transform(XAxis, calibrationAngle_).ApplyTo(&gravity);
    }
    *acceleration_ = gravity;
}


}    // Namespace Game.
}    // Namespace kxm.
