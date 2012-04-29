//
//  AccelerometerTask.cpp
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Game/AccelerometerTask.h>

#include <kxm/Vectoid/Vector.h>

#import <CoreMotion/CMMotionManager.h>

using boost::shared_ptr;
using namespace kxm::Vectoid;


namespace kxm {
namespace Game {

AccelerometerTask::AccelerometerTask()
    : acceleration_(new Vector()) {
    CMMotionManager *manager = [[CMMotionManager alloc] init];
    [manager retain];
    [manager startAccelerometerUpdates];
    //[manager startDeviceMotionUpdates];
    motionManager_ = manager;
}

AccelerometerTask::~AccelerometerTask() {
    CMMotionManager *manager = (CMMotionManager *)motionManager_;
    [manager stopAccelerometerUpdates];
    //[manager stopDeviceMotionUpdates];
    [manager release];
}

shared_ptr<const Vector> AccelerometerTask::Acceleration() const {
    return acceleration_;
}

void AccelerometerTask::Execute() {
    CMAcceleration acceleration = ((CMMotionManager *)motionManager_).accelerometerData
                                                                     .acceleration;
    acceleration_->x = acceleration.x;
    acceleration_->y = acceleration.y;
    acceleration_->z = acceleration.z;
}


}    // Namespace Game.
}    // Namespace kxm.
