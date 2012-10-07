//
//  Particles.h
//  kxm
//
//  Created by Kai Hergenroether on 5/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#ifndef KXM_VECTOID_PARTICLES_H_
#define KXM_VECTOID_PARTICLES_H_


#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <kxm/Core/ItemGroups.h>
#include <kxm/Vectoid/Vector.h>


namespace kxm {
namespace Vectoid {

//! Manages a set of particles.
/*!
 *  \ingroup Vectoid
 *
 *  Particles generally have quite a limited lifetime: They get added to the particle set, move
 *  around for some time, and then they die. To avoid unnecessary re-allocations of particle data
 *  structures, two sets of particles are maintained internally: <i>active</i> particles and
 *  <i>idle</i> particles. The active particles are those currently in the particle set as visible
 *  to the outside, whereas the idle particles form the pool from where particle info structures are
 *  fetched whenever a new particle needs to be <i>activated</i> (= addded to the visible particle
 *  set).
 */
class Particles {
  public:
    //! Holds information about a particle.
    /*!
     *  \ingroup Vectoid
     */
    struct ParticleInfo {
        Vector position,
               velocity;
        float  age;
        bool   hidden;
        float  random0, random1;    // Random numbers in [0, 1].
        
        ParticleInfo();
    };
    
    //! Well, constructor.
    Particles();
    //! Adds a new particle with specified starting position and velocity, and provides access to
    //! it.
    ParticleInfo *AddParticle(const Vector &position, const Vector &velocity);
    //! Tells the number of active particles.
    int Count();
    //! Returns an iterator for the active particles.
    Core::ItemGroups<ParticleInfo>::Iterator GetIterator();
    
  private:
    Core::ItemGroups<ParticleInfo>            particles_;
    int                                       activeGroup_;
    boost::random::mt19937                    randomGenerator_;
    boost::random::uniform_int_distribution<> random1000_;
    
    Particles(const Particles &other);
    Particles &operator=(const Particles &other);

};


}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_PARTICLES_H_
