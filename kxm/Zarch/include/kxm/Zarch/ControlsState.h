//
//  ControlsState.h
//  kxm
//
//  Created by Kai Hergenroether on 6/7/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_CONTROLSSTATE_H_
#define KXM_ZARCH_CONTROLSSTATE_H_


#include <kxm/Vectoid/Vector.h>


namespace kxm {
namespace Zarch {

//! Holds the current state of the input controls.
/*!
 *  \ingroup Zarch
 */
struct ControlsState {
    Vectoid::Vector orientationInput;
    bool            thrusterRequested,
                    firingRequested;
};


}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_CONTROLSSTATE_H_
