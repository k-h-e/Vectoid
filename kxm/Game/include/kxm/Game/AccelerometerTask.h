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
    
    //! Grants read-only access to the vector where the task maintains the current reading from the
    //! device accelerometer.
    boost::shared_ptr<const Vectoid::Vector> Acceleration() const;
    void Execute();
    
  private:
    AccelerometerTask(const AccelerometerTask &other);
    AccelerometerTask &operator=(const AccelerometerTask &other);
    
    boost::shared_ptr<Vectoid::Vector> acceleration_;
    void                               *motionManager_;
};


}
}


#endif    // KXM_GAME_ACCELEROMETERTASK_H_

