//
//  Particles.cpp
//  kxm
//
//  Created by Kai Hergenroether on 5/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Vectoid/Particles.h>

#include <kxm/Core/CompactPool.h>
#include <kxm/Core/NumberTools.h>

using namespace std;
using namespace boost;
using namespace boost::random;
using namespace kxm::Core;


namespace kxm {
namespace Vectoid {

Particles::Particles()
        : numParticles_(0),
          random1000_(uniform_int_distribution<>(0, 1000)) {
    particles_ = shared_ptr<CompactPool<ParticleNode> >(new CompactPool<ParticleNode>(16, 64));
    particleAnchor_.next = 0;
}

Particles::~Particles() {
    // As the particle pool might be shared, we properly put back our particles.
    Iterator iter = GetIterator();
    while (iter.Next())
        iter.Remove();
}

Particles::ParticleInfo *Particles::AddParticle(const Vector &position, const Vector &velocity) {
    ParticleNode *node = particles_->Get();
    node->next = particleAnchor_.next;
    particleAnchor_.next = node;
    ++numParticles_;
    
    ParticleInfo *particle = &node->info;
    particle->position = position;
    particle->velocity = velocity;
    particle->age      = 0.0f;
    particle->hidden   = false;
    if (!particle->random0) {
        // Use random generator only once for each particle info: initially.
        particle->random0 = (float)random1000_(randomGenerator_)/500.0f - 1.0f;
        particle->random1 = (float)random1000_(randomGenerator_)/500.0f - 1.0f;
        NumberTools::Clamp(&particle->random0, -1.0f, 1.0f);
        NumberTools::Clamp(&particle->random1, -1.0f, 1.0f);

    }
    return particle;
}

int Particles::Count() {
    return numParticles_;
}

Particles::Iterator Particles::GetIterator() {
    return Iterator(this);
}

Particles::ParticleInfo::ParticleInfo()
    : age(0.0f),
      hidden(false),
      random0(0.0f),
      random1(0.0f) {
}

Particles::Iterator::Iterator(Particles *particles)
        : particles_(particles),
          particlePool_(particles->particles_.get()),
          lastNode_(&particles->particleAnchor_),
          currentNode_(0) {
}

Particles::ParticleInfo *Particles::Iterator::Next() {
    if (!currentNode_) {
        currentNode_ = lastNode_->next;
    }
    else {
        lastNode_    = currentNode_;
        currentNode_ = lastNode_->next;
    }
    if (currentNode_)
        return &currentNode_->info;
    else
        return 0;
}

void Particles::Iterator::Remove() {
    if (currentNode_) {
        lastNode_->next = currentNode_->next;
        particlePool_->Put(currentNode_);
        currentNode_ = 0;
        --particles_->numParticles_;
    }
}


}    // Namespace Vectoid.
}    // Namespace kxm.
