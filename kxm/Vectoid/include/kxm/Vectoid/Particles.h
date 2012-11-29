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

#include <boost/shared_ptr.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

#include <kxm/Vectoid/Vector.h>


namespace kxm {

namespace Core {
    template<class T> class CompactPool;
}

namespace Vectoid {

//! Manages a set of particles.
/*!
 *  \ingroup Vectoid
 *
 *  Particles generally have quite a limited lifetime: They get created, move around for some time,
 *  and then they die. To avoid unnecessary re-allocations of particle data structures, pooling is
 *  used. */
class Particles {
  private:
    struct ParticleNode;    // Needed in public nested class below.

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
    
    //! Allows to iterate over the particles, and also to delete particles.
    /*!
     *  \ingroup Vectoid
     */
    class Iterator {
      public:
        Iterator(Particles *particles);
        //! Advances to the next particle and returns it, or returns <c>0</c> in case there are no
        //! more particles.
        ParticleInfo *Next();
        //! Removes the current particle from the set (if there is one), without invalidating the
        //! iterator.
        void Remove();
    
      private:
        Particles                       *particles_;
        Core::CompactPool<ParticleNode> *particlePool_;
        ParticleNode                    *lastNode_,
                                        *currentNode_;
    };
    
    Particles();
    ~Particles();
    //! Adds a new particle with specified starting position and velocity, and provides access to
    //! it.
    ParticleInfo *AddParticle(const Vector &position, const Vector &velocity);
    //! Tells the number of particles.
    int Count();
    //! Returns an iterator for the active particles.
    Iterator GetIterator();
    
  private:
    struct ParticleNode {
        ParticleNode *next;
        ParticleInfo info;
    };
    
    Particles(const Particles &other);
    Particles &operator=(const Particles &other);
    
    boost::shared_ptr<Core::CompactPool<ParticleNode> > particles_;    // Might be shared, someday.
    ParticleNode                                        particleAnchor_;
    int                                                 numParticles_;
    boost::random::mt19937                              randomGenerator_;
    boost::random::uniform_int_distribution<>           random1000_;
};


}    // Namespace Vectoid.
}    // Namespace kxm.


#endif    // KXM_VECTOID_PARTICLES_H_
