//
//  AccelerometerTask.h
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_GAME_ACCELEROMETERTASK_H_
#define KXM_GAME_ACCELEROMETERTASK_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Game/TaskInterface.h>


namespace kxm {

namespace Vectoid {
    class Vector;
}

namespace Game {

//! Fetches device orientation data from the accelerometer.
/*!
 *  \ingroup Game
 */
class AccelerometerTask : public virtual TaskInterface {
  public:
    AccelerometerTask();
    ~AccelerometerTask();
    
    //! Grants read-only access to the vector where the task maintains the current gravity reading
    //! from the device accelerometer.
    boost::shared_ptr<const Vectoid::Vector> Gravity() const;
    //! Toogles panning override mode.
    void EnablePanningOverride(bool enabled);
    //! In panning override mode, this method is used to inform the task about panning updates. 
    void UpdatePanningOverride(float x, float y);
    
    void Execute();
    
  private:
    AccelerometerTask(const AccelerometerTask &other);
    AccelerometerTask &operator=(const AccelerometerTask &other);
    
    boost::shared_ptr<Vectoid::Vector> acceleration_;
    void                               *motionManager_;
    float                              calibrationAngle_;
    float                              panningOverrideX_,    // Only valid if override enabled.
                                       panningOverrideY_;    // Only valid if override enabled.
    bool                               panningOverrideEnabled_;
};


}
}


#endif    // KXM_GAME_ACCELEROMETERTASK_H_

