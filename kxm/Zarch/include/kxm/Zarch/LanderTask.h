//
//  LanderTask.h
//  kxm
//
//  Created by Kai Hergenroether on 4/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_LANDERTASK_H_
#define KXM_ZARCH_LANDERTASK_H_


#include <boost/shared_ptr.hpp>

#include <kxm/Game/TaskInterface.h>

/*!
 *  \defgroup Zarch Game inspired by Zarch
 */


namespace kxm {

namespace Vectoid {
    class Vector;
    class Transform;
    class CoordSysInterface;
}

namespace Zarch {

//! Controls the lander (the vehicle controlled by the player).
/*!
 *  \ingroup Zarch
 */
class LanderTask : public virtual Game::TaskInterface {
  public:
    LanderTask(boost::shared_ptr<Vectoid::CoordSysInterface> landerCoordSys,
               boost::shared_ptr<const Vectoid::Vector> acceleration);
    
    //! Grants read-only access to the transform where the task maintains the lander's position and
    //! orientation.
    boost::shared_ptr<const Vectoid::Transform> LanderTransform();
    void Execute();
    
  private:
    LanderTask(const LanderTask &other);
    LanderTask &operator=(const LanderTask &other);
    
    boost::shared_ptr<Vectoid::CoordSysInterface> landerCoordSys_;
    boost::shared_ptr<const Vectoid::Vector>      acceleration_;
    boost::shared_ptr<Vectoid::Transform>         landerTransform_;
    float                                         animationAngle_;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_LANDERTASK_H_
