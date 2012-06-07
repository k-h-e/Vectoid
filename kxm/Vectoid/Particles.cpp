//
//  Particles.cpp
//  kxm
//
//  Created by Kai Hergenroether on 5/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//


#include <kxm/Vectoid/Particles.h>

#include <kxm/Core/NumberTools.h>

using namespace std;
using namespace::boost::random;
using namespace kxm::Core;


namespace kxm {
namespace Vectoid {

Particles::Particles() {
    activeAnchorId_ = AddParticleInfo();
    idleAnchorId_   = AddParticleInfo();
    numActive_      = 0;
    numIdle_        = 0;
    random1000_     = uniform_int_distribution<>(0, 1000);
}

Particles::ParticleInfo *Particles::AddParticle(const Vector &position, const Vector &velocity) {
    ParticleInfo *particle = ActivateParticle();
    particle->position = position;
    particle->velocity = velocity;
    particle->age      = 0.0f;
    particle->hidden   = false;
    return particle;
}

void Particles::RemoveParticles(const vector<int> &particlesToRemove) {
    for (vector<int>::const_iterator iter = particlesToRemove.begin();
         iter != particlesToRemove.end(); ++iter) {
        UnlinkParticleInfo(*iter);
        --numActive_;
        LinkInParticleInfo(*iter, idleAnchorId_);
        ++numIdle_;       
    }
}

int Particles::Count() {
    return numActive_;
}

Particles::Iterator Particles::BeginIteration() {
    return Iterator(&particles_, activeAnchorId_); 
}

Particles::ParticleInfo *Particles::ActivateParticle() {
    int newId = particles_[idleAnchorId_].nextId_;
    if (newId == idleAnchorId_) {
        newId = AddParticleInfo();
    }
    else {
        UnlinkParticleInfo(newId);
        --numIdle_;
    }
    LinkInParticleInfo(newId, activeAnchorId_);
    ++numActive_;
    return &particles_[newId];
}

void Particles::DeactivateParticle(int id) {
    UnlinkParticleInfo(id);
    --numActive_;
    LinkInParticleInfo(id, idleAnchorId_);
    ++numIdle_;
}

void Particles::LinkInParticleInfo(int id, int prevId) {
    ParticleInfo &particle = particles_[id],
                 &prev     = particles_[prevId];
    int          nextId    = prev.nextId_;
    ParticleInfo &next     = particles_[nextId];
    prev.nextId_     = id;
    particle.prevId_ = prevId;
    particle.nextId_ = nextId;
    next.prevId_     = id;
}

void Particles::UnlinkParticleInfo(int id) {
    ParticleInfo &particle = particles_[id],
                 &prev     = particles_[particle.prevId_],
                 &next     = particles_[particle.nextId_];
    prev.nextId_ = particle.nextId_;
    next.prevId_ = particle.prevId_;
    particle.prevId_ = id;
    particle.nextId_ = id;
}

int Particles::AddParticleInfo() {
    int id = (int)particles_.size();
    ParticleInfo particle;
    particle.prevId_ = id;
    particle.nextId_ = id;
    particle.random0 = (float)random1000_(randomGenerator_)/500.0f - 1.0f;
    particle.random1 = (float)random1000_(randomGenerator_)/500.0f - 1.0f;
    NumberTools::Clamp(&particle.random0, -1.0f, 1.0f);
    NumberTools::Clamp(&particle.random1, -1.0f, 1.0f);
    particles_.push_back(particle);
    return id;
}

Particles::Iterator::Iterator(vector<ParticleInfo> *particles, int activeAnchorId)
        : particles_(particles),
          currentId_(activeAnchorId),
          activeAnchorId_(activeAnchorId) {
}

Particles::ParticleInfo *Particles::Iterator::Next() {
    int nextId = (*particles_)[currentId_].nextId_;
    if (nextId == activeAnchorId_) {
        return 0;
    }
    else {
        currentId_ = nextId;
        return &(*particles_)[currentId_];
    }
}

int Particles::Iterator::CurrentId() {
    if (currentId_ == activeAnchorId_)
        return 0;
    else
        return currentId_;
}


}    // Namespace Vectoid.
}    // Namespace kxm.
