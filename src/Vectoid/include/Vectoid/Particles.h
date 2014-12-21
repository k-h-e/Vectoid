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
#include <memory>
#include <random>

#include <kxm/Core/ReusableItems.h>
#include <Vectoid/Vector.h>


namespace kxm {
namespace Vectoid {

//! Manages a set of particles.
/*!
 *  \ingroup Vectoid
 *
 *  Particles have quite a limited lifetime: They get created, move around for some time, and then
 *  they die. To avoid unnecessary re-allocations of particle data structures, pooling is used
 *  transparently.
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
    
    Particles();
    //! Adds a new particle with specified starting position and velocity, and provides access to
    //! it.
    ParticleInfo &Add(const Vector &position, const Vector &velocity);
    //! Removes the specified particle.
    void Remove(int id);
    //! Tells the number of particles.
    int Count();
    //! Returns an iterator for the particles.
    Core::ReusableItems<ParticleInfo>::Iterator GetIterator();
    
  private:
    Particles(const Particles &other);
    Particles &operator=(const Particles &other);
    
    Core::ReusableItems<ParticleInfo> particles_;
    std::default_random_engine        randomEngine_;
    std::uniform_int_distribution<>   random1000_;
};


}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_PARTICLES_H_
