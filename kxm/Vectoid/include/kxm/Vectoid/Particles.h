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

#include <kxm/Core/Interface.h>
#include <kxm/Vectoid/Vector.h>


namespace kxm {
namespace Vectoid {

//! Manages a set of particles.
/*!
 *  \ingroup Vectoid
 *
 *  Particles generally have quite a limited lifetime: The get added to the particle set, move
 *  around for some time, and then they die. To avoid unnecessary re-allocations of particle data
 *  structures, two sets of particles are maintained internally: <i>active</i> particles and
 *  <i>idle</i> particles. The active particles are those currently in the particle set as visible
 *  to the outside, whereas the idle particles form the pool from where particle info structures are
 *  fetched whenever a new particle needs to be <i>activated</i> (= addded to the visible particle
 *  set).
 *
 *  Internally, particles are identified via non-negative integer ids, appropriately pointing into
 *  the particle info buffer.
 */
class Particles : public virtual Core::Interface {
  public:
    class ParticleInfo {
      public:
        Vector position,
               velocity;
        float  age;
        float  random0, random1;    // Random numbers in [0, 1].
      private:
        friend class Particles;
        int prevId_, nextId_;       // Linkage, both the particle's id if particle is not linked in.
    };
    
    class Iterator {
      public:
        Iterator(std::vector<ParticleInfo> *particles, int activeAnchorId);
        
        //! Advanced the iterator to the next particle, and returns it. In case there are no more
        //! particles, the method returns <c>0</c>.
        ParticleInfo *Next();
        //! Returns the id for the particle currently pointed to by the iterator, or <c>-1</c> in
        //! case Next() has not yet been successfully called.
        int CurrentId();
        
      private:
        // Objects may be copied.
        
        std::vector<ParticleInfo> *particles_;
        int                       currentId_,
                                  activeAnchorId_;  
    };
    
    Particles();
    
    //! Adds a new particle with specified starting position and velocity, and returns its state
    //! object.
    ParticleInfo *AddParticle(const Vector &position, const Vector &velocity);
    //! Removes the particles for the specified ids.
    void RemoveParticles(const std::vector<int> &particlesToRemove);
    //! Tells the number of (active) particles.
    int Count();
    //! Returns an iterator for the (active) particles.
    Iterator BeginIteration();
    
  private:
    Particles(const Particles &other);
    Particles &operator=(const Particles &other);
    
    //! Takes a particle from the idle pool, activates it and returns it. If currently there is
    //! no idle particle, a new one is automatically created and activated.
    ParticleInfo *ActivateParticle();
    //! Removes the specified (active!) particle from the active set and puts it into the idle pool.
    void DeactivateParticle(int id);
    //! Links in the specified (unlinked!) particle info as successor to the particle info given as
    //! <c>prevId</c>.
    void LinkInParticleInfo(int id, int prevId);
    //! Unlinks the specified (linked-in!) particle info.
    void UnlinkParticleInfo(int id);
    //! Adds a new particle info object to the end of the buffer, links it back upon itself, and
    //! returns its id.
    int AddParticleInfo();
    
    std::vector<ParticleInfo>                 particles_;
    int                                       activeAnchorId_, idleAnchorId_,
                                              numActive_,      numIdle_;
    boost::random::mt19937                    randomGenerator_;
    boost::random::uniform_int_distribution<> random1000_;
};


}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_PARTICLES_H_
