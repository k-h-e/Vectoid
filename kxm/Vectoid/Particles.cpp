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
using namespace kxm::Core;


namespace kxm {
namespace Vectoid {

Particles::Particles()
        : particles_(1),
          random1000_(uniform_int_distribution<>(0, 1000)) {
}

Particles::ParticleInfo &Particles::Add(const Vector &position, const Vector &velocity) {
    ParticleInfo &particle = particles_.Get(0);
    particle.position = position;
    particle.velocity = velocity;
    particle.age      = 0.0f;
    particle.hidden   = false;
    if (!particle.random0) {
        // Use random generator only once for each particle info: initially.
        particle.random0 = (float)random1000_(randomEngine_)/500.0f - 1.0f;
        particle.random1 = (float)random1000_(randomEngine_)/500.0f - 1.0f;
        NumberTools::Clamp(&particle.random0, -1.0f, 1.0f);
        NumberTools::Clamp(&particle.random1, -1.0f, 1.0f);

    }
    return particle;
}

void Particles::Remove(int id) {
    particles_.Put(id);
}

int Particles::Count() {
    return particles_.Count() - particles_.IdleCount();
}

ReusableItems<Particles::ParticleInfo>::Iterator Particles::GetIterator() {
    return particles_.GetIterator(0);
}

Particles::ParticleInfo::ParticleInfo()
    : age(0.0f),
      hidden(false),
      random0(0.0f),
      random1(0.0f) {
}

}    // Namespace Vectoid.
}    // Namespace kxm.
