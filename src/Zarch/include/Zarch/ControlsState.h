//
//  ControlsState.h
//  kxm
//
//  Created by Kai Hergenroether on 6/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_CONTROLSSTATE_H_
#define KXM_ZARCH_CONTROLSSTATE_H_


#include <Vectoid/Vector.h>


namespace kxm {
namespace Zarch {

//! Holds the current state of the input controls.
/*!
 *  \ingroup Zarch
 */
struct ControlsState {
    ControlsState() : thruster(false), trigger(false) {}
    Vectoid::Vector orientation;
    bool            thruster,
                    trigger;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_CONTROLSSTATE_H_
