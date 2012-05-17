//
//  MapParameters.h
//  kxm
//
//  Created by Kai Hergenroether on 5/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_ZARCH_MAPPARAMETERS_H_
#define KXM_ZARCH_MAPPARAMETERS_H_


namespace kxm {
namespace Zarch {

//! Centrally holds parameters for a given map ("world", "level", ...).
/*!
 *  \ingroup Zarch
 */
struct MapParameters {
    const float gravity,
                landerThrust,
                maxThrusterParticleAge,
                thrusterExhaustVelocity,
                thrusterExhaustInterval,
                thrusterParticleSpread,
                thrusterJetSize;
    
    MapParameters()
        : gravity(3.0f),
          landerThrust(10.0f),
          maxThrusterParticleAge(3.0f),
          thrusterExhaustVelocity(3.0f),
          thrusterExhaustInterval(.01f),
          thrusterParticleSpread(.25f),
          thrusterJetSize(.1f * .65f) {
    }
};

}    // Namespace Zarch.
}    // Namespace kxm.


#endif    // KXM_ZARCH_MAPPARAMETERS_H_
